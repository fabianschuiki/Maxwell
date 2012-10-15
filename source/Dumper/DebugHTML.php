<?php
namespace Dumper;
use Store\Manager;

class DebugHTML
{
	protected $entityIDs;
	
	public function __construct()
	{
		$this->entityIDs = array();
	}
	
	public function addEntityID($id)
	{
		$this->entityIDs[] = $id;
	}
	
	public function addEntityIDs($ids)
	{
		$this->entityIDs = array_merge($this->entityIDs, $ids);
	}
	
	static private function entityInfo(\Entity\Node $entity = null)
	{
		if (!$entity) return "&lt;nothing&gt;";
		return $entity->getID()." ".vartype($entity);
	}
	
	static private function typeInfo(\Type\Type $type = null)
	{
		if (!$type) return "&lt;unknown&gt;";
		if ($type instanceof \Type\Generic) return "*";
		if ($type instanceof \Type\Builtin) return "builtin {$type->getName()}";
		if ($type instanceof \Type\Defined) return $type->getDefinition()->getName();
		throw new \exception("unable to generate type info for ".vartype($type));
	}
	
	static private function idify(\Entity\Node $entity)
	{
		return "entity-".str_replace(".", "-", $entity->getID());
	}
	
	public function run()
	{
		$manager = Manager::get();
		$entityStore = $manager->getEntityStore();
		
		$title = "Entity ".implode(", ", $this->entityIDs);
		$head  = "<style>".file_get_contents(__DIR__."/DebugHTML.css")."</style>\n";
		$head .= "<script src=\"http://code.jquery.com/jquery-1.8.2.min.js\" type=\"text/javascript\"></script>\n";
		$head .= "<script type=\"text/javascript\">".file_get_contents(__DIR__."/DebugHTML.js")."</script>\n";
		$body  = "";
		
		foreach ($this->entityIDs as $entityID) {
			$html = "";
			$root = $entityStore->getEntity($entityID);
			
			$wrappers = array();
			$stack = array($root);
			
			while (count($stack)) {
				$entity = array_shift($stack);
				$stack = array_merge($stack, $entity->getChildEntities());
				
				$class_paths = array();
				foreach (explode("\\", strtolower(vartype($entity))) as $cls) {
					if (count($class_paths))
						$cls = $class_paths[count($class_paths)-1] . "-$cls";
					$class_paths[] = $cls;
				}
				$classes = implode(" ", $class_paths);
				
				$attrs = "";
				$info = "<div class=\"entity-info\">";
				$info .= "<div class=\"name\">{$entity->getID()} <span class=\"class\">".vartype($entity)."</span></div>";
				if (isset($entity->analysis)) {
					if (isset($entity->analysis->binding)) {
						$info .= "<h1>Binding</h1>\n";
						$t = $entity->analysis->binding->target;
						$info .= "<div>Target: ".static::entityInfo($t)."</div>\n";
						if ($t) $attrs .= " data-bindingTarget=\"".static::idify($t)."\"";
					}
					if (isset($entity->analysis->type)) {
						$info .= "<h1>Type</h1>\n";
						$info .= "<div>Initial: ".static::typeInfo($entity->analysis->type->initial)."</div>";
						$info .= "<div>Inferred: ".static::typeInfo($entity->analysis->type->inferred)."</div>";
						$info .= "<div>Required: ".static::typeInfo($entity->analysis->type->required)."</div>";
					}
					if (isset($entity->compiler)) {
						$info .= "<h1>Compiler</h1>\n";
						$compiler = $entity->compiler;
						$fields = array();
						if ($compiler instanceof \Compiler\Node\TypeDefinition) {
							$fields["Name"] = $compiler->getName();
							$fields["Local Name"] = $compiler->getLocalName();
						}
						if ($compiler instanceof \Compiler\Node\VarDef) {
							$fields["Name"] = $compiler->getName();
							$fields["Type"] = static::typeInfo($compiler->getType());
							$fields["RefType"] = $compiler->getRefType();
							$fields["C Type"] = $compiler->getCType();
						}
						foreach ($fields as $name => $str) {
							$info .= "<div>$name: $str</div>\n";
						}
					}
				}
				$info .= "</div>";
				
				$tag = "<div class=\"entity-tag\">{$entity->getID()}</div>";
				
				
				$r = $entity->getRange();
				$wrappers[] = array('r' => $r, 'a' => "<span id=\"".static::idify($entity)."\" class=\"$classes\" $attrs>", 'b' => "</span>");
				$wrappers[] = array('r' => $entity->getHumanRangeIfPossible(), 'a' => "<span class=\"human\">$tag", 'b' => "$info</span>");
			}
			
			$range = $root->getRange();
			$source = substr($range->getFile()->getContents(), $range->getPosition(), $range->getLength());
			
			$appliedWrappers = array();
			foreach ($wrappers as $wrapper) {
				$ins_a = $wrapper['r']->getStart()->getOffset();
				$ins_b = $wrapper['r']->getEnd()->getOffset();
				
				//Shift the insertion locations according to the already applied wrappers.
				$sa = 0;
				$sb = 0;
				foreach ($appliedWrappers as $aw) {
					$r = $aw['r'];
					if ($r->getStart()->getOffset() <= $ins_a) $sa += strlen($aw['a']);
					if ($r->getStart()->getOffset() <= $ins_b) $sb += strlen($aw['a']);
					if ($r->getEnd()->getOffset() < $ins_a) $sa += strlen($aw['b']);
					if ($r->getEnd()->getOffset() < $ins_b) $sb += strlen($aw['b']);
				}
				$ins_a += $sa - $range->getPosition();
				$ins_b += $sb - $range->getPosition();
				
				$source = substr($source, 0, $ins_a).$wrapper['a'].substr($source, $ins_a, $ins_b-$ins_a).$wrapper['b'].substr($source, $ins_b);
				
				$appliedWrappers[] = $wrapper;
			}
			$html .= "<pre>$source</pre>";
			
			$body .= $html;
		}
		
		$html = "<html><head><title>$title</title> $head</head><body>$body</body></html>";
		file_put_contents($manager->getDirectory()."/debug.html", $html);
	}
}
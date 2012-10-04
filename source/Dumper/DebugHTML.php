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
	
	public function run()
	{
		$manager = Manager::get();
		$entityStore = $manager->getEntityStore();
		
		$title = "Entity ".implode(", ", $this->entityIDs);
		$head  = "<style>".file_get_contents(__DIR__."/DebugHTML.css")."</style>";
		$head .= "<script type=\"text/javascript\">".file_get_contents(__DIR__."/DebugHTML.js")."</script>";
		$body  = "";
		
		foreach ($this->entityIDs as $entityID) {
			$html = "<h1>Entity $entityID</h1>";
			$root = $entityStore->getEntity($entityID);
			
			$wrappers = array();
			$stack = array($root);
			
			while (count($stack)) {
				$entity = array_shift($stack);
				$stack = array_merge($stack, $entity->getChildEntities());
				
				$classes = implode(" ", explode("\\", strtolower(vartype($entity))));
				
				$info = "<div class=\"entity-info\">";
				$info .= "<div class=\"name\">{$entity->getID()} <span class=\"class\">".vartype($entity)."</span></div>";
				$info .= "</div>";
				
				$r = $entity->getRange();
				$wrappers[] = array('r' => $r, 'a' => "<span id=\"e{$entity->getID()}\" class=\"$classes\">", 'b' => "</span>");
				$wrappers[] = array('r' => $entity->getHumanRangeIfPossible(), 'a' => "<span class=\"human\">", 'b' => "$info</span>");
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
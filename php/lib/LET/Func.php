<?php
namespace LET;

abstract class Func extends TypedNode
{
	public $specializations;
	public $id;
	
	abstract function name();
	abstract function inputs();
	abstract function outputs();
	abstract function stmts();
	abstract function subscope();
	
	public function __construct()
	{
		$this->id = trim(`uuidgen`);
	}
	
	public function details()
	{
		$det = function($arg){ return $arg->details(); };
		return "'{$this->name()}' {$this->argDetails()}";
	}
	
	public function argDetails()
	{
		$det = function($arg){ return $arg->details(); };
		return "(".implode(", ", array_map($det, $this->inputs())).") -> (".implode(", ", array_map($det, $this->outputs())).")";
	}
	
	public function nice()
	{
		$str = "Function '{$this->name()}'";
		if (!$this->isSpecific()) $str = "Generic $str";
		return $str;
	}
	
	public function children()
	{
		return array_merge(
			$this->inputs(),
			$this->outputs(),
			$this->subscope()->children(),
			$this->stmts()
		);
	}
	
	public function unconstrainedType()
	{
		return new FuncType($this->scope, $this->argsType($this->inputs()), $this->argsType($this->outputs()));
	}
	
	public function type() { return $this->unconstrainedType(); }
	public function imposeTypeConstraint(Type $type) { trigger_error("Func {$this->details()} should not have type constraints.", E_USER_ERROR); }
	
	private function argsType(array $args)
	{
		$fields = array();
		foreach ($args as $arg) {
			$name = $arg->name();
			$type = $arg->type();
			if ($type) {
				if ($name[0] == '~') {
					$fields[] = $type;
				} else {
					$fields[$arg->name()] = $type;
				}
			}
		}
		return new TypeTuple($this->scope, $fields);
	}
	
	public function isSpecific()
	{
		return $this->type()->isSpecific();
	}
	
	public function specialize(FuncType $type, array &$specializations)
	{
		$thisType = $this->type();
		$inter = Type::intersect($thisType, $type, $thisType->scope);
		if (Type::equal($inter, $thisType)) return $this;
		
		/*if ($this->name() == '-') {
			echo "\033[1mdeciding whether to specialize\033[0m {$this->details()} for {$type->details()}\n";
			echo "  this type:    {$thisType->details()}\n";
			echo "  intersection: {$inter->details()}\n";
			foreach ($inter as $k => $v) {
				if (!isset($thisType->$k)) continue;
				if ($thisType->$k instanceof Type && $inter->$k instanceof Type) {
					echo "inter->$k == thisType->$k: ".(Type::equal($thisType->$k, $inter->$k) ? 'yes' : 'no')."\n";
				}
			}
			//letDumpNPause();
		}*/
		
		if ($this->specializations) {
			foreach ($this->specializations as $spec) {
				$specType = $spec->type();
				$inter = Type::intersect($specType, $type);
				//NOTE: this might cause some trouble as it potentially returns a more specialized function than was requested. If problems arise, use Type::equal instead. 
				if ($inter) return $spec;
			}
		} else {
			$this->specializations = array();
		}
		
		foreach (array($type->in(), $type->out()) as $tuple) {
			foreach ($tuple->fields as $name => $arg) {
				if (!$arg instanceof MemberConstrainedType || !$arg->type instanceof ConcreteType) continue;
				//echo "specialization for $name\n";
				$tuple->fields[$name] = $arg->type->specialize($arg, $specializations);
			}
		}
		
		\mwc\debug("\033[1mspecializing\033[0m {$this->details()} for {$type->details()}\n");
		$spec = new Func_Spec($this, $type);
		$this->specializations[] = $spec;
		$specializations[] = $spec;
		$this->scope->add($spec);
		return $spec;
	}
	
	public function notifyTypeChanged()
	{
		$this->scope->notifyNodeChangedType($this);
	}
	
	/*public function maybeTypeChanged()
	{
		$type = $this->type();
		if ($type != $this->lastConfirmedType && $this->lastConfirmedType) {
			echo "\033[32;1mtype changed\033[0m for {$this->desc()}\n";
			$this->scope->notifyNodeChangedType($this);
		}
		$this->lastConfirmedType = $type;
	}*/
	
	public function reduceToInterface(Scope $scope)
	{
		return new Func_Intf($scope, $this);
	}
	
	public function reduceToAbsolute(Scope $scope)
	{
		return new Func_Proxy($scope, $this->id);
	}
}
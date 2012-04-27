<?php
namespace LET;

class ConcreteType_Intf extends ConcreteType
{
	public $name;
	public $members;
	
	public function __construct(Scope $scope, ConcreteType $type)
	{
		parent::__construct();
		
		if (!$type->subscope) {
			echo "missing subscope for ".get_class($type)."\n";
			debug_print_backtrace(DEBUG_BACKTRACE_IGNORE_ARGS);
		}
		$subscope = $type->subscope->reduceToInterface($scope);
		$subscope->node = $this;
		
		$members = array();
		foreach ($type->members() as $member) {
			$members[] = $member->reduceToInterface($subscope);
		}
		
		$this->id       = $type->id;
		$this->name     = strval($type->name());
		$this->members  = $members;
		$this->subscope = $subscope;
		$this->scope    = $scope;
	}
	
	public function name()    { return $this->name; }
	public function members() { return $this->members; }
	
	public function reduceToInterface() { throw new \RuntimeException("ConcreteType_Intf should never be asked for reduction"); }
	
	public function specialize(MemberConstrainedType $type, array &$specializations)
	{
		$root = $this->scope->rootNode();
		assert($root instanceof Root);
		
		$reduced = $type->reduceToAbsolute(new Scope);
		$reduced->originalID = $this->id;
		foreach ($root->specializations as $id => $spec) {
			/*if (Type::equalTwo($spec, $reduced))*/if ($spec->originalID === $this->id) return /*$type*/new ConcreteType_Proxy($id);
		}
		
		$id = trim(`uuidgen`);
		$root->specializations[$id] = $reduced;
		return /*$type*/new ConcreteType_Proxy($id);
	}
	
	public function registerExternal(Root $root)
	{
		$root->externalNodes[] = $this->id;
	}
	
	public function gatherExternalNodeIDs(array &$ids)
	{
		$ids[] = $this->id;
	}
}
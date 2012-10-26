<?php
namespace Analysis\Node\Call;

class Callee extends \Analysis\Node\Node
{
	public $type;
	public $binding;
	
	public function __construct(\Entity\Expr\Call\Callee $entity)
	{
		parent::__construct($entity);
		$this->type = new \Analysis\Type;
		$this->binding = new \Analysis\Binding;
	}
	
	protected $candidates;
	
	public function setCandidates(array $c) { $this->candidates = $c; }
	public function getCandidates() { return $this->candidates; }
}
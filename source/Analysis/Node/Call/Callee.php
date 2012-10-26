<?php
namespace Analysis\Node\Call;

class Callee extends \Analysis\Node\Node
{
	public $type;
	
	public function __construct(\Entity\Expr\Call\Callee $entity)
	{
		parent::__construct($entity);
		$this->type = new \Analysis\Type;
	}
	
	protected $candidates;
	
	public function setCandidates(array $c) { $this->candidates = $c; }
	public function getCandidates() { return $this->candidates; }
}
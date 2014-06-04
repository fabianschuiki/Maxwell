<?php
namespace LET\InferredType;

class Func extends Base
{
	public $in;
	public $out;
	
	public function __construct(Tuple $in, Tuple $out)
	{
		$this->in  = $in;
		$this->out = $out;
	}
	
	public function details()
	{
		return "($this->in->details()) -> ($this->out->details())";
	}
}
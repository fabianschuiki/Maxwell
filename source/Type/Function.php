<?php
namespace Type;

/** Function type that represents a mapping from one type to another. */
class Function extends Type
{
	static public function makeWithArgs(Type $input, Type $output)
	{
		$t = new self;
		$t->generateId();
		$t->setInput($input);
		$t->setOutput($output);
		return $t;
	}
	
	protected $input;
	protected $output;
	
	public function setInput(Type $i) { $this->input = $i; }
	public function getInput() { return $this->input; }
	
	public function setOutput(Type $o) { $this->output = $o; }
	public function getOutput() { return $this->output; }
}
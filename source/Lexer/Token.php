<?php
namespace Lexer;
use Source\Range;

class Token extends AbstractToken
{
	protected $id;
	protected $type;
	protected $text;
	protected $range;
	
	public function __construct($id, $type, $text, Range $range)
	{
		assert(is_numeric($id) && is_string($type) && is_string($text));
		$this->id = $id;
		$this->type = $type;
		$this->text = $text;
		$this->range = $range;
	}
	
	public function getID()    { return $this->id; }
	public function getType()  { return $this->type; }
	public function getText()  { return $this->text; }
	public function getRange() { return $this->range; }
	public function getFile()  { return $this->range->getFile(); }
}

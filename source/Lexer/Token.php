<?php
namespace Lexer;
use Source\Range;

class Token extends AbstractToken
{
	protected $type;
	protected $text;
	protected $range;
	
	public function __construct($type, $text, Range $range)
	{
		$this->type = $type;
		$this->text = $text;
		$this->range = $range;
	}
	
	public function getType()   { return $this->type; }
	public function getText()   { return $this->text; }
	public function getRange()  { return $this->range; }
	public function getFile()   { return $this->range->getFile(); }
}

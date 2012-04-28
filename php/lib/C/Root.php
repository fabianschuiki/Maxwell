<?php
namespace C;

class Root extends Container
{
	public function getHeader() { return $this->getCode(true); }
	public function getSource() { return $this->getCode(false); }
	
	private function getCode($header = false)
	{
		$str = "";
		foreach ($this->nodes as $node) {
			assert($node instanceof Func || $node instanceof Type);
			$str .= ($header ? $node->getDeclaration() : $node->getDefinition())."\n";
		}
		return $str;
	}
}
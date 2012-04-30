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
			assert($node instanceof Func || $node instanceof TypeDef);
			$d = null;
			if ($header) {
				$d = $node->getDeclaration();
			} else {
				$d = $node->getDefinition();
			}
			if ($d) $str .= "$d\n";
		}
		return $str;
	}
}
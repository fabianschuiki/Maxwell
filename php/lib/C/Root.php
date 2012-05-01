<?php
namespace C;

class Root extends Container
{
	public $requiredHeaders = array();
	
	public function getHeader() { return $this->getCode(true); }
	public function getSource() { return $this->getCode(false); }
	
	private function getCode($header = false)
	{
		$str = "";
		
		if (!$header) {
			foreach ($this->requiredHeaders as $h) {
				$str .= "#include \"$h\"\n";
			}
			if ($str) $str .= "\n";
		}
		
		foreach ($this->nodes as $node) {
			assert($node instanceof Func || $node instanceof TypeDef || $node instanceof GlobalVar);
			$d = null;
			if ($header) {
				$d = $node->getDeclaration();
			} else {
				$d = $node->getDefinition();
			}
			if ($d) $str .= "$d\n\n";
		}
		return $str;
	}
}
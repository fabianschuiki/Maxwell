<?php
namespace Coder;

class XMLCoder
{
	public function encode(Element $root)
	{
		$output = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";
		$output .= $this->encodeElement($root)."\n";
		return $output;
	}
	
	protected function encodeElement(Element $e)
	{
		$output = "<{$e->getName()}";
		foreach ($e->getAttributes() as $name => $value) {
			$output .= " $name=\"".htmlspecialchars($value)."\"";
		}
		if ($e->hasElements()) {
			$output .= ">\n";
			foreach ($e->getElements() as $c) {
				$co = $this->encodeElement($c);
				$output .= "\t".str_replace("\n", "\n\t", $co)."\n";
			}
			$output .= "</{$e->getName()}>";
		} else {
			$output .= " />";
		}
		return $output;
	}
	
	public function decode()
	{
	}
}
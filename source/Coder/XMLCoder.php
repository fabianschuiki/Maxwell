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
	
	public function encodeToFile(Element $root, $file)
	{
		file_put_contents($file, $this->encode($root));
	}
	
	protected function encodeElement(Element $e, $indent = 0)
	{
		$output = "<{$e->getName()}";
		foreach ($e->getAttributes() as $name => $value) {
			$output .= " $name=\"".htmlspecialchars($value)."\"";
		}
		$tabs = str_repeat("\t", $indent);
		if ($e->hasElements()) {
			$output .= ">\n$tabs";
			foreach ($e->getElements() as $c) {
				$co = $this->encodeElement($c, $indent + 1);
				$output .= "\t"./*str_replace("\n", "\n\t", */$co/*)*/."\n$tabs";
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
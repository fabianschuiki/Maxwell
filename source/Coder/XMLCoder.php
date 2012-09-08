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
	
	protected function encodeElement(Element $e)
	{
		$unsafe = "\n\r\t";
		$output = "<{$e->getName()}";
		foreach ($e->getAttributes() as $name => $value) {
			$safe = htmlspecialchars($value);
			for ($i = 0; $i < strlen($unsafe); $i++)
				$safe = str_replace($unsafe[$i], "&#".ord($unsafe[$i]).";", $safe);
			$output .= " $name=\"".$safe."\"";
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
	
	public function decode($xml_string)
	{
		$xml = new \SimpleXMLElement($xml_string);
		if (!$xml) return null;
		return $this->decodeElement($xml);
	}
	
	public function decodeFromFile($file)
	{
		$e = $this->decode(file_get_contents($file));
		if (!$e)
			throw new \exception("Unable to parse file '$file'.");
		return $e;
	}
	
	protected function decodeElement(\SimpleXMLElement $xml)
	{
		$e = new Element($xml->getName());
		foreach ($xml->attributes() as $attribute => $value) {
			$e->setAttribute(strval($attribute), strval($value));
		}
		foreach ($xml->children() as $name => $child) {
			$e->addElement($this->decodeElement($child));
		}
		return $e;
	}
}
<?php

class SourceColorizer
{
	public $input;
	public $tokens;
	public $output;
	
	public function colorize()
	{
		$this->output = <<<EOF
<style>
pre { color: #aaa; }
span.identifier, span.symbol, span.keyword { color: #000000; }
span.numeric { color: #3465a4; }
span.keyword { font-weight: bold; }
span.string { color: #3465a4; }

</style>
EOF;
		
		$this->output .= "<pre>";
		$s = 0;
		
		foreach ($this->tokens as $t) {
			$e = $t->range->start->offset;
			$this->output .= substr($this->input, $s, $e-$s);
			$s = $e;
			
			$e = $t->range->end->offset;
			$this->output .= '<span class="'.$t->type.'">';
			$this->output .= substr($this->input, $s, $e-$s);
			$this->output .= '</span>';
			$s = $e;
		}
		
		$this->output .= substr($this->input, $s);
		$this->output .= "</pre>";
	}
}

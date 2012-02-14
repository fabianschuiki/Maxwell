<?php

class SourceColorizer
{
	public $input;
	public $flatTokens;
	public $output;
	
	public function colorize()
	{
		$this->output = "";
		$s = 0;
		
		foreach ($this->flatTokens as $t) {
			$e = $t->range->start->offset;
			$this->output .= substr($this->input, $s, $e-$s);
			$s = $e;
			
			$context = (isset($t->context) ? $t->context : '');
			
			$e = $t->range->end->offset;
			$this->output .= '<span class="'.$t->type.' '.str_replace('.', '-', $context).'"';
			$this->output .= ' data-context="'.$context.'"';
			$this->output .= '>';
			$this->output .= substr($this->input, $s, $e-$s);
			$this->output .= '</span>';
			$s = $e;
		}
		
		$this->output .= substr($this->input, $s);
	}
}

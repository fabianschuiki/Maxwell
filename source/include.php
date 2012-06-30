<?php
$ENABLE_COLORS = (`tput colors` > 2);

function vartype($v)
{
	if (is_object($v))
		return get_class($v);
	return gettype($v);
}
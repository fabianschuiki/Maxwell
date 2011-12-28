<?php
function square($in) {
$out = array();
/* return from square */
$out['r'] = ($in['x'] * $in['x']);
goto square_return;
square_return:
return $out;
}

$var_r_double = null /* not yet able to call functions */;

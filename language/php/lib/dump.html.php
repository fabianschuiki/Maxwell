<?php

function dumpDefType(Node $type)
{
	$out = "<div class=\"scp-type\">\n";
	$out .= "<span class=\"scp-name\">{$type->name}</span>\n";
	if ($type->primitive) {
		$out .= "<span class=\"scp-attr\">primitive</span>\n";
	}
	$out .= "</div>\n";
	return $out;
}

function dumpScope(Scope $scope)
{
	$out = "<div class=\"scp\">\n";
	if (count($scope->types)) {
		$out .= "<h1>Types</h1>\n";
		foreach ($scope->types as $name => $type) {
			$out .= dumpDefType($type);
		}
	}
	$out .= "</div>\n";
	return $out;
}

?>
<html>
	<head>
		<title><?php echo basename($file->path); ?></title>
		<script type="text/javascript" src="http://code.jquery.com/jquery-1.7.1.min.js"></script>
		<style><?php include __DIR__.'/dump.css'; ?></style>
	</head>

	<body>
		<div class="col left top">
			<pre class="code"><?php
			$s = 0;
			$i = 0;
			foreach ($tokens as $t) {
				$e = $t->range->start->offset;
				echo substr($file->content, $s, $e-$s);
				$s = $e;
			
				$context = (isset($t->context) ? $t->context : '');
			
				$e = $t->range->end->offset;
				$t->index = $i++;
				echo '<span id="token-'.($t->index).'" class="'.$t->type.' '.str_replace('.', '-', $context).'"';
				echo ' data-context="'.$context.'"';
				echo '>';
				echo substr($file->content, $s, $e-$s);
				echo '</span>';
				$s = $e;
			}
			?></pre>
		</div>
		<div class="col left bottom">
			<?php echo dumpScope($scope); ?>
		</div>
		<div class="col right">
			<div class="nodes">
			<?php
			function dumpNodes($nodes) {
				foreach ($nodes as $n) {
					echo '<div class="node">';
					echo '<span class="kind">'.$n->kind.'</span>';
					echo '<div class="attrs">';
					foreach ($n as $key => $value) {
						if ($key == 'kind' || is_array($value) || $value instanceof Node) continue;
						echo '<div class="attr">';
						echo '<span class="key">'.$key.'</span>: ';
						if ($value instanceof Token) {
							echo '<span class="value token">'.$value->text.'</span>';
						}
						if ($value instanceof Type) {
							echo '<span class="value type">'.implode(', ',$value->types).'</span>';
						}
						if ($value instanceof TypeSet) {
							echo '<span class="value type">'.$value.'</span>';
						}
						if ($value instanceof Scope) {
							$scp = $value;
							$names = array();
							while ($scp) {
								$names = array_merge($names, $scp->names);
								$scp = $scp->parent;
							}
							$jsscope = "\$('#scope{$value->index}')";
							echo '<a onmouseover="'.$jsscope.'.show()" onmouseout="'.$jsscope.'.hide()">'.count($names).' names</a>';
							echo '<div id="scope'.$value->index.'" class="scope" style="display: none;">';
							foreach ($names as $name => $sn) {
								echo '<div class="scope-entry">';
								echo '<span class="scope-name">'.$name.'</span>';
								echo ' = ';
								echo '<span class="scope-kind">'.$sn->kind.'</span>';
								echo '</div>';
							}
							echo '</div>';
							//echo '…';
						}
						if (is_string($value)) {
							echo '<span class="value string">'.$value.'</span>';
						}
						if (is_bool($value)) {
							echo '<span class="value bool">'.($value ? 'yes' : 'no').'</span>';
						}
						echo '</div>';
					}
					echo '</div>';
					echo '<div class="subnodes">';
					$printed = false;
					foreach ($n as $key => $value) {
						if ($key == 'nodes') continue;
						if ($value instanceof Node || is_array($value)) {
							echo '<span class="name">'.$key.'</span>: ';
							if ($key == 'a_target') {
								echo '<span style="color: #4e9a06;">bound to '.$value->kind.'</span>';
							} else {
								dumpNodes(is_array($value) ? $value : array($value));
							}
							$printed = true;
						}
					}
					if (!$printed && isset($n->nodes)) {
						echo '<span class="name">nodes</span>:';
						dumpNodes($n->nodes);
					}
					echo '</div>';
					echo '</div>';
				}
			}
			dumpNodes($nodes);
			?>
			</div>
		</div>
	</body>
</html>

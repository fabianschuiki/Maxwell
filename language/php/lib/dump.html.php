<?php

function tokenHover(Token &$t)
{
	$pairs = array();
	$pairs['Token'] = $t->type;
	if (isset($t->node)) {
		$pairs['Node'] = $t->node->kind;
		if (isset($t->node->a_types)) {
			$pairs['Types'] = $t->node->a_types;
		}
		if (isset($t->node->a_target)) {
			$ts = $t->node->a_target;
			if (is_array($ts)) {
				$targets = array();
				foreach ($ts as $t) {
					$targets[] = "{$t->kind} {$t->name} {$t->a_types}";
				}
				$target = "[".implode(",\n", $targets)."]";
			} else {
				$target = "{$ts->kind} {$ts->name} {$ts->a_types}";
			}
			$pairs['Bound To'] = $target;
		}
	}
	
	$lines = array();
	foreach ($pairs as $key => $value) {
		$class = strtolower(is_object($value) ? get_class($value) : 'string');
		$l  = "<div class=\"token-hover-line\">";
		$l .= "<span class=\"key\">$key: </span><span class=\"value value-$class\">$value</span>";
		$l .= "</div>";
		$lines[] = $l;
	}
	return implode('', $lines);
}

?>
<html>
	<head>
		<title><?php echo basename($file->path); ?></title>
		<script type="text/javascript" src="http://code.jquery.com/jquery-1.7.1.min.js"></script>
		<style><?php include __DIR__.'/dump.css'; ?></style>
		
		<script type="text/javascript">
		$(document).ready(function(){
			$("span.token").each(function(_, e){
				$(e).mouseover(function(){
					console.log(this);
					$(this).children("div.hover").first().show();
				});
				$(e).mouseout(function(){
					$(this).children("div.hover").first().hide();
				});
			});
		});
		</script>
	</head>

	<body>
		<div class="col left">
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
				echo "<span id=\"token-{$t->index}\" class=\"token\">";
				echo "<span class=\"{$t->type} ".str_replace('.', '-', $context)."\" data-context=\"$context\">";
				echo substr($file->content, $s, $e-$s);
				echo "</span>";
				echo "<div class=\"hover\">";
				echo tokenHover($t);
				echo "</div>";
				echo "</span>";
				$s = $e;
			}
			?></pre>
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
						if ($value instanceof TypeSet || $value instanceof FuncType || $value instanceof TupleType) {
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

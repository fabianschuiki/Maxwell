<html>
	<head>
		<title><?php echo basename($file->path); ?> - LET</title>
		<script type="text/javascript" src="http://code.jquery.com/jquery-1.7.1.min.js"></script>
		<style><?php @include __DIR__.'/let.css'; ?></style>
		<script type="text/javascript"><?php @include __DIR__.'/let.js'; ?></script>
	</head>
	
	<?php
	
		function dumpScope(LET\Scope $scope)
		{
			$str = "<div class=\"scope\">";
			$entities = array();
			$fields = array('types', 'funcs');
			foreach ($fields as $field) {
				if (!count($scope->$field)) continue;
				$str .= "<div class=\"$field\">";
				foreach ($scope->$field as $entity) {
					$str .= "<pre>".$entity->desc()."</pre>";
					if ($field == 'funcs') $str .= dumpFunc($entity);
				}
				$str .= "</div>";
			}
			$str .= "</div>";
			return $str;
		}
		
		function dumpFunc(LET\Func $func)
		{
			$str = "<div class=\"func\">";
			if ($func->subscope) $str .= dumpScope($func->subscope);
			foreach ($func->stmts as $stmt) {
				$str .= "<div class=\"stmt\">{$stmt->desc()}</div>";
				$str .= dumpNode($stmt);
			}
			$str .= "</div>";
			return $str;
		}
		
		function dumpNode(LET\Node $node)
		{
			$str = "<div class=\"node\">{$node->details()}";
			$str .= "<div class=\"kind\">{$node->kind()}</div>";
			if ($node instanceof LET\Expr) {
				$type = $node->type();
				$class = ($type instanceof LET\ConcreteType ? 'concrete' : ''); 
				$str .= "<div class=\"type $class\">".($type ? $type->details() : '?')."</div>";
			}
			foreach ($node->children() as $child) {
				$str .= dumpNode($child);
			}
			$str .= "</div>";
			return $str;
		}
	
	?>
	
	<body><?php echo dumpScope($analyzer->scope); ?></body>
</html>
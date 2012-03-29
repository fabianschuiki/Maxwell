<html>
	<head>
		<title><?php echo basename($file->path); ?> - LET</title>
		<script type="text/javascript" src="http://code.jquery.com/jquery-1.7.1.min.js"></script>
		<style><?php @include __DIR__.'/let.css'; ?></style>
		<script type="text/javascript"><?php @include __DIR__.'/let.js'; ?></script>
	</head>
	
	<?php
		if (!function_exists('dumpScope')):
		
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
					if ($field == 'types') $str .= dumpType($entity);
					if ($field == 'funcs') $str .= dumpFunc($entity);
				}
				$str .= "</div>";
			}
			$str .= "</div>";
			return $str;
		}
		
		function dumpType(LET\ConcreteType $type)
		{
			$str = "<div class=\"type indent\">";
			if ($type->subscope) $str .= dumpScope($type->subscope);
			foreach ($type->members as $member) $str .= dumpNode($member);
			$str .= "</div>";
			return $str;
		}
		
		function dumpFunc(LET\Func $func)
		{
			$str = "<div class=\"func indent\">";
			if ($func->subscope) $str .= dumpScope($func->subscope);
			foreach ($func->stmts as $stmt) $str .= dumpNode($stmt);
			$str .= "</div>";
			return $str;
		}
		
		function dumpNode(LET\Node $node, $root = true)
		{
			$details = ($root ? $node->desc() : $node->details());
			$str = "<div class=\"node\">$details";
			$str .= "<div class=\"kind\">{$node->kind()}</div>";
			if ($node instanceof LET\Ident && !$node->boundTo) {
				$str .= "<div class=\"unbound\">unbound</div>";
			}
			if (method_exists($node, 'type')) {
				$type = $node->type();
				$class = ($type instanceof LET\Type && $type->isSpecific() ? 'specific' : ''); 
				$str .= "<div class=\"type $class\">".($type ? $type->details() : '?')."</div>";
			}
			if (method_exists($node, 'typeConstraint')) {
				$type = $node->typeConstraint();
				if ($type && $type != $node->type()) $str .= "<div class=\"type constraint\">".$type->details()."</div>";
			}
			foreach ($node->children() as $child) {
				if ($child instanceof LET\Type && $child->isSpecific()) continue;
				if ($child instanceof LET\GenericType) continue;
				$str .= dumpNode($child, false);
			}
			$str .= "</div>";
			return $str;
		}
		
		endif;
	?>
	
	<body><?php echo dumpScope($analyzer->scope); ?></body>
</html>
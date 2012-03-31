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
				$entities = $scope->$field;
				usort($entities, function($a,$b){ return strcmp($a->name(), $b->name()); });
				foreach ($entities as $entity) {
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
			$str = "<div class=\"type\"><div class=\"name\">".htmlentities($type->desc())."</div>";
			if (!$type->isSpecific()) $str .= "<div class=\"attrs\">generic</div>";
			$str .= "<div class=\"indent\">";
			if ($type->subscope) $str .= dumpScope($type->subscope);
			foreach ($type->members() as $member) $str .= dumpNode($member);
			$str .= "</div></div>";
			return $str;
		}
		
		function dumpFunc(LET\Func $func)
		{
			$str = "<div class=\"func\"><div class=\"name\">".htmlentities($func->desc())."</div>";
			if (!$func->isSpecific()) $str .= "<div class=\"attrs\">generic</div>";
			$str .= "<div class=\"indent\">";
			if ($func->subscope) $str .= dumpScope($func->subscope);
			$args = array_merge($func->inputs(), $func->outputs());
			if (count($args)) {
				foreach ($args as $arg) $str .= dumpNode($arg);
				$str .= "<hr/>";
			}
			foreach ($func->stmts() as $stmt) $str .= dumpNode($stmt);
			$str .= "</div></div>";
			return $str;
		}
		
		function dumpNode(LET\Node $node, $root = true)
		{
			$details = ($root ? $node->desc() : $node->details());
			$str = "<div class=\"node\">".htmlentities($details);
			$str .= "<div class=\"kind\">{$node->kind()}</div>";
			if ($node instanceof LET\Ident && !$node->boundTo) {
				$str .= "<div class=\"unbound\">unbound</div>";
			}
			if ($node instanceof LET\TypedNode) {
				$type = $node->type();
				$uncon = $node->unconstrainedType();
				$class = ($type instanceof LET\Type && $type->isSpecific() ? 'specific' : ''); 
				$str .= "<div class=\"type $class\">".($type ? htmlentities($type->details()) : ($uncon ? "(".htmlEntities($uncon->details()).")" : '?'))."</div>";
				$constraint = $node->typeConstraint;
				if ($constraint && $constraint != $node->type()) $str .= "<div class=\"type constraint\">".htmlentities($constraint->details())."</div>";
			}
			foreach ($node->children() as $child) {
				if ($child instanceof LET\Type && $child->isSpecific()) continue;
				if ($child instanceof LET\GenericType || $child instanceof LET\ConcreteType) continue;
				$str .= dumpNode($child, false);
			}
			$str .= "</div>";
			return $str;
		}
		
		endif;
	?>
	
	<body><?php echo dumpScope($analyzer->scope); ?></body>
</html>
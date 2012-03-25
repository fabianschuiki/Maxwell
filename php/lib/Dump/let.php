<html>
	<head>
		<title><?php echo basename($file->path); ?></title>
		<script type="text/javascript" src="http://code.jquery.com/jquery-1.7.1.min.js"></script>
		<style><?php @include __DIR__.'/let.css'; ?></style>
		<script type="text/javascript"><?php @include __DIR__.'/let.js'; ?></script>
	</head>
	
	<?php
	
		function dumpScope(LET\Scope $scope)
		{
			$entities = array();
			$fields = array('types', 'funcs');
			foreach ($fields as $field) {
				$entities = array_merge($entities, array_map(function($entity){ return $entity->desc(); }, $scope->$field));
			}
			return implode("\n", $entities);
		}
	
	?>
	
	<body><?php echo dumpScope($analyzer->scope); ?></body>
</html>
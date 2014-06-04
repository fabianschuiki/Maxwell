<html>
	<head>
		<title><?php echo basename($file->path); ?> - AST</title>
		<script type="text/javascript" src="http://code.jquery.com/jquery-1.7.1.min.js"></script>
		<style><?php @include __DIR__.'/ast.css'; ?></style>
		<script type="text/javascript"><?php @include __DIR__.'/ast.js'; ?></script>
	</head>

	<body><?php
		$s = 0;
		$i = 0;
		foreach ($lexer->flatTokens as $token) {
			$e = $token->range->start->offset;
			echo str_replace("\t", "    ", substr($file->content, $s, $e-$s));
			$s = $e;
		
			$e = $token->range->end->offset;
			$text = str_replace("\t", "    ", substr($file->content, $s, $e-$s));
			$s = $e;
			
			echo "<span class=\"token {$token->type}\">$text</span>";
		}
	?></body>
</html>
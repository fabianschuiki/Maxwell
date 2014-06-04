all: test.frontend.php test.analyzer.php test.compiler.php compile

compile:
	gcc -o ../build/tests/frontend/compiled ../build/tests/frontend/code/*.c

.PHONY: *.php
*.php:
	php $@
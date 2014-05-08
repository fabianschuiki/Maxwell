# Copyright (c) 2014 Fabian Schuiki
# Configuration file that tests the parser against the Maxwell source files
# listed in this directory.

file(GLOB_RECURSE mw_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.mw)

foreach(f ${mw_files})
	add_test(parse-${f} ${CMAKE_BINARY_DIR}/source/test/mwcparse ${CMAKE_CURRENT_SOURCE_DIR}/${f})
endforeach()

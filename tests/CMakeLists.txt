# Copyright (c) 2014 Fabian Schuiki
# Configuration file that tests the parser against the Maxwell source files
# listed in this directory.

# file(GLOB_RECURSE mw_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.mw)
file(GLOB_RECURSE syntax_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} syntax/*.mw)
file(GLOB_RECURSE stage_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} stage/*.mw)

configure_file(syntax.sh ${CMAKE_CURRENT_BINARY_DIR}/syntax.sh @ONLY)
configure_file(stage.sh ${CMAKE_CURRENT_BINARY_DIR}/stage.sh @ONLY)

# foreach(f ${mw_files})
# 	add_test(parse-${f} ${CMAKE_BINARY_DIR}/maxwell/test/mwcparse ${CMAKE_CURRENT_SOURCE_DIR}/${f})
# endforeach()

foreach(f ${syntax_files})
	add_test(${f} ${CMAKE_CURRENT_BINARY_DIR}/syntax.sh ${CMAKE_CURRENT_SOURCE_DIR}/${f})
endforeach()

foreach(f ${stage_files})
	add_test(${f} ${CMAKE_CURRENT_BINARY_DIR}/stage.sh ${CMAKE_CURRENT_SOURCE_DIR}/${f})
endforeach()

# Copyright (c) 2014 Fabian Schuiki
add_library(base64 base64.cpp)
add_library(sqlite3 ${PROJECT_SOURCE_DIR}/thirdparty/sqlite3.c)
target_link_libraries(sqlite3 dl pthread)

add_subdirectory(driver)
add_subdirectory(gen)
add_subdirectory(ast)
add_subdirectory(stage)
add_subdirectory(test)
add_subdirectory(backend)

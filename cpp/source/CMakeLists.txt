add_library(base64 base64.cpp)
add_library(sqlite3 sqlite3.c)

add_subdirectory(driver)
add_subdirectory(gen)
add_subdirectory(ast)
add_subdirectory(stage)
add_subdirectory(test)
add_subdirectory(backend)
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

# mwc-src
add_executable(mwc-src
	filesystem/disk/DiskDirectory.cpp
	filesystem/disk/DiskFile.cpp
	filesystem/Path.cpp
	repository/file/FileSourceRepository.cpp
	sha1.cpp
	mwc/SourceTool-main.cpp
	mwc/SourceTool.cpp
	mwc/Tool.cpp)
target_link_libraries(mwc-src ${Boost_LIBRARIES})

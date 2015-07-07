# Copyright (c) 2014 Fabian Schuiki
add_library(sqlite3 ${PROJECT_SOURCE_DIR}/thirdparty/sqlite3.c)
target_link_libraries(sqlite3 dl pthread)

# Create the configuration header.
configure_file(config.hpp.in config.hpp)
include_directories("${PROJECT_BINARY_DIR}")

add_subdirectory(driver)
add_subdirectory(gen)
add_subdirectory(ast)
add_subdirectory(stage)
add_subdirectory(test)
add_subdirectory(backend)

# libmwc-common
add_library(obj-common
	filesystem/disk/DiskDirectory.cpp
	filesystem/disk/DiskFile.cpp
	filesystem/Path.cpp
	repository/file/FileSource.cpp
	repository/file/FileSourceRepository.cpp
	base64.cpp
	sha1.cpp
)

# mwc-src
add_executable(mwc-src
	mwc/SourceTool-main.cpp
	mwc/SourceTool.cpp
	mwc/Tool.cpp
)
target_link_libraries(mwc-src obj-common ${Boost_LIBRARIES})

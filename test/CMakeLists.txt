# Copyright (c) 2014 Fabian Schuiki
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/maxwell)

add_executable(test-repository-source
	repository/source.cpp
	${SOURCE_DIR}/repository/SourceIndex.cpp)

add_executable(test-serialization
	serialization.cpp)

target_link_libraries(test-repository-source ${Boost_LIBRARIES})
target_link_libraries(test-serialization ${Boost_LIBRARIES})

add_test(repository/source test-repository-source)
add_test(serialization test-serialization)

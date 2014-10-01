# Copyright (c) 2014 Fabian Schuiki
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/maxwell)

add_executable(test-repository-source
	repository/source.cpp
	${SOURCE_DIR}/repository/file/FileSourceRepository.cpp
	${SOURCE_DIR}/sha1.cpp)
add_executable(test-serialization serialization.cpp)
add_executable(test-location location.cpp)
add_executable(test-sha1
	sha1.cpp
	${SOURCE_DIR}/sha1.cpp)

target_link_libraries(test-repository-source ${Boost_LIBRARIES})
target_link_libraries(test-serialization ${Boost_LIBRARIES})
target_link_libraries(test-location ${Boost_LIBRARIES})
target_link_libraries(test-sha1 ${Boost_LIBRARIES})

add_test(repository/source test-repository-source)
add_test(serialization test-serialization)
add_test(location test-location)
add_test(sha1 test-sha1)

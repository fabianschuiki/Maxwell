# Copyright (c) 2014 Fabian Schuiki
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/maxwell)

add_executable(test-repository-source repository/source.cpp)
add_executable(test-serialization serialization.cpp)
add_executable(test-location location.cpp)
add_executable(test-sha1 sha1.cpp)
add_executable(test-filesystem-path filesystem-path.cpp)
add_executable(test-base64 base64.cpp)

target_link_libraries(test-repository-source obj-common ${Boost_LIBRARIES})
target_link_libraries(test-serialization obj-common ${Boost_LIBRARIES})
target_link_libraries(test-location obj-common ${Boost_LIBRARIES})
target_link_libraries(test-sha1 obj-common ${Boost_LIBRARIES})
target_link_libraries(test-base64 obj-common ${Boost_LIBRARIES})
target_link_libraries(test-filesystem-path obj-common ${Boost_LIBRARIES})

add_test(repository/source test-repository-source)
add_test(serialization test-serialization)
add_test(location test-location)
add_test(sha1 test-sha1)
add_test(base64 test-base64)
add_test(filesystem/path test-filesystem-path)

# Copyright (c) 2014 Fabian Schuiki
add_executable(test-repository-source source.cpp ${SOURCE_DIR}/repository/SourceIndex.cpp)
target_link_libraries(test-repository-source ${Boost_LIBRARIES})
add_test(repository/source test-repository-source)

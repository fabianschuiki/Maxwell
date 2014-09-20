# Copyright (c) 2014 Fabian Schuiki
add_executable(test-serialization serialization.cpp)
target_link_libraries(test-serialization ${Boost_LIBRARIES})
add_test(serialization test-serialization)

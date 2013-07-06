add_executable(astsrcrepo astsrcrepo.cpp)
add_executable(astnoderepo astnoderepo.cpp)
add_executable(astserializer astserializer.cpp)
add_executable(base64 base64.cpp)

target_link_libraries(astsrcrepo ast ${Boost_LIBRARIES})
target_link_libraries(astnoderepo ast ${Boost_LIBRARIES})
target_link_libraries(astserializer ast ${Boost_LIBRARIES})
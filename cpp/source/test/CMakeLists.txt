add_executable(astsrcrepo astsrcrepo.cpp)
add_executable(astnoderepo astnoderepo.cpp)

target_link_libraries(astsrcrepo ast ${Boost_LIBRARIES})
target_link_libraries(astnoderepo ast ${Boost_LIBRARIES})
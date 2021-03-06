add_executable(astsrcrepo astsrcrepo.cpp)
add_executable(astnoderepo astnoderepo.cpp)
add_executable(astserializer astserializer.cpp)
add_executable(mwcparse mwcparse.cpp)
add_executable(mwcstage mwcstage.cpp)
add_executable(mwcdump mwcdump.cpp)
add_executable(mwcbendc mwcbendc.cpp)
add_executable(mwcbendcpkg mwcbendcpkg.cpp)

target_link_libraries(astsrcrepo ast obj-common ${Boost_LIBRARIES})
target_link_libraries(astnoderepo ast obj-common ${Boost_LIBRARIES})
target_link_libraries(astserializer ast obj-common ${Boost_LIBRARIES})
target_link_libraries(mwcparse ast driver obj-common ${Boost_LIBRARIES})
target_link_libraries(mwcstage ast stage obj-common ${Boost_LIBRARIES})
target_link_libraries(mwcdump ast obj-common ${Boost_LIBRARIES})
target_link_libraries(mwcbendc ast backendc sqlite3 stage obj-common ${Boost_LIBRARIES})
target_link_libraries(mwcbendcpkg ast backendc sqlite3 stage obj-common ${Boost_LIBRARIES})

# Add unit tests if the corresponding boost library is found.
if (Boost_UNIT_TEST_FRAMEWORK_FOUND)
	add_executable(test-parser parser/detail.cpp parser/tests.cpp)
	target_link_libraries(test-parser driver ${Boost_LIBRARIES} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
	add_test(parser test-parser)
endif()

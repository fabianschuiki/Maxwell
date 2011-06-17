cmake_minimum_required(VERSION 2.6)
project(maxwell)

set(sources
	main.c
)

add_executable(
	maxwell
	${sources}
)
target_link_libraries(
	maxwell
)

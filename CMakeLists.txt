project(game)
cmake_minimum_required(VERSION 2.6)

find_package(SDL REQUIRED)
include_directories(${SDL_INCLUDE_DIR})

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	add_definitions(-DDEBUG)
endif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")

set( SOURCES
	widget.cpp
	map.cpp
	menu.cpp
	main.cpp )

add_executable(game ${SOURCES})
target_link_libraries(game ${SDL_LIBRARY})

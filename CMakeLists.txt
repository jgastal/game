set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project(game)
cmake_minimum_required(VERSION 2.6)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	add_definitions(-DDEBUG)
endif("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")

set( SOURCES
	map.cpp
	menu.cpp
	main.cpp )

add_definitions(-Wno-c++0x-extensions)

add_executable(game ${SOURCES})
target_link_libraries(game widget)

find_package(SDL REQUIRED)
include_directories(${SDL_INCLUDE_DIR})

find_package(SDL_image REQUIRED)
include_directories(${SDLIMAGE_INCLUDE_DIR})

find_package(SDL_ttf REQUIRED)
include_directories(${SDLTTF_INCLUDE_DIR})

add_subdirectory(libwidget)
include_directories(libwidget)

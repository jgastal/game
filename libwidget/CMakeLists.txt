find_package(Boost 1.40.0 REQUIRED COMPONENTS signals)

include_directories(${Boost_INCLUDE_DIRS})

set(SOURCES
	application.cpp
	widget.cpp
	rect.cpp
	button.cpp
	image.cpp)

option(LIBWIDGET_AUTO_FREE "Delete all widgets on application end" OFF)

if(LIBWIDGET_AUTO_FREE)
	add_definitions(-DLIBWIDGET_AUTO_FREE)
endif(LIBWIDGET_AUTO_FREE)

add_library(widget SHARED ${SOURCES})
target_link_libraries(widget ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${SDLTTF_LIBRARY} ${Boost_LIBRARIES})

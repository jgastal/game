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
target_link_libraries(widget ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${SDLTTF_LIBRARY})

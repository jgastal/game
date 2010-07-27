set(SOURCES
	widget.cpp
	rect.cpp
	button.cpp)

add_library(widget SHARED ${SOURCES})
target_link_libraries(widget ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${SDLTTF_LIBRARY})

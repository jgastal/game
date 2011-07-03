set(SOURCES
	signal.hpp
	slot.hpp)

add_definitions(-Wno-c++0x-extensions)

add_library(signal SHARED ${SOURCES})
set_target_properties(signal PROPERTIES LINKER_LANGUAGE C)

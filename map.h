#ifndef MAP_H
#define MAP_H

#include "widget.h"

class Map : public Widget
{
	public:
		Map();

	protected:
		virtual void paint(SDL_Surface* surface);
};

#endif // MAP_H

#include "map.h"
#include <SDL.h>

Map::Map()
{
}

void Map::paint(SDL_Surface* surface)
{
	Uint32 green = SDL_MapRGB(surface->format, 0, 0xff, 0);
	SDL_FillRect(surface, NULL, green);
}

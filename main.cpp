#include <SDL.h>
#include <list>
#include "menu.h"
#include "map.h"

int main(int argc, char **argv)
{
	Widget::initVideo();
	int width = SDL_GetVideoSurface()->w;
	int height = SDL_GetVideoSurface()->h;

	Menu *menu = new Menu();
	menu->resize(width / 5 < 200 ? 200 : width / 5, height);
	menu->move(width - menu->getGeometry().w, 0);
	Map *map = new Map();
	map->resize(width - menu->getGeometry().w, height);

	Widget::runEventLoop();
	delete menu;
	delete map;

	return 0;
}

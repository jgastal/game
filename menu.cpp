#include "menu.h"
#include <SDL.h>

Menu::Menu()
{
	color = true;
}

void Menu::paint(SDL_Surface* surface)
{
	static bool colorInit = false;
	if(!colorInit)
	{
		blue = SDL_MapRGB(surface->format, 0, 0, 0xff);
		red = SDL_MapRGB(surface->format, 0xff, 0, 0);
		colorInit = true;
	}
	if(color)
		SDL_FillRect(surface, NULL, blue);
	else
		SDL_FillRect(surface, NULL, red);
}

void Menu::leftClicked(SDL_MouseButtonEvent* event)
{
	color = !color;
	update();
}

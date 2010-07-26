#include "menu.h"
#include <SDL.h>

Menu::Menu()
{
	status = true;
	setColor(blue);
}

void Menu::leftClicked(SDL_MouseButtonEvent* event)
{
	status = !status;
	if(status)
		setColor(blue);
	else
		setColor(red);
}

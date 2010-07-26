#ifndef MENU_H
#define MENU_H

#include "widget.h"
#include <rect.h>

struct SDL_MouseButtonEvent;
struct SDL_Surface;

class Menu : public Rect
{
	public:
		Menu();

	protected:
		virtual void leftClicked(SDL_MouseButtonEvent* event);

	private:
		bool status;
};

#endif // MENU_H

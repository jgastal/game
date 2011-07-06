#ifndef MENU_H
#define MENU_H

#include "button.h"

struct SDL_MouseButtonEvent;

class Menu : public libwidget::Rect
{
	public:
		Menu();
		void changeColor(SDL_MouseButtonEvent* event);

	private:
		void close(SDL_MouseButtonEvent *ev);
		bool status;
		libwidget::Button *bt;
};

#endif // MENU_H

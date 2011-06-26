#ifndef MENU_H
#define MENU_H

#include <rect.h>

struct SDL_MouseButtonEvent;

class Menu : public libwidget::Rect
{
	public:
		Menu();
		void changeColor(SDL_MouseButtonEvent* event);

	private:
		void close(SDL_MouseButtonEvent *ev);
		bool status;
		Rect *bt;
};

#endif // MENU_H

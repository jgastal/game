#ifndef MENU_H
#define MENU_H

#include "widget.h"

struct SDL_MouseButtonEvent;
struct SDL_Surface;

class Menu : public Widget
{
	public:
		Menu();

	protected:
		virtual void leftClicked(SDL_MouseButtonEvent* event);
		virtual void paint(SDL_Surface* surface);

	private:
		bool color;
		int red, blue;
};

#endif // MENU_H

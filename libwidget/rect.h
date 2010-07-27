#ifndef RECT_H
#define RECT_H

#include "widget.h"

class Rect : public Widget
{
	public:
		Rect(Widget *parent = 0);
		void setColor(SDL_Color c);
		SDL_Color getColor() const;

	protected:
		virtual void paint(SDL_Surface* surface);

	private:
		SDL_Color color;
};

#endif // RECT_H

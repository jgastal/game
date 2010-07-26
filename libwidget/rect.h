#ifndef RECT_H
#define RECT_H

#include "widget.h"

class Rect : public Widget
{
	public:
		Rect();
		void setColor(int c);
		int getColor() const;

		static int red;
		static int blue;

	protected:
		virtual void paint(SDL_Surface* surface);

	private:
		int color;
};

#endif // RECT_H

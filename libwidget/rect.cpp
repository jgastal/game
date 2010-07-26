#include "rect.h"
#include <SDL.h>

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	int Rect::red = 0xff0000;
	int Rect::green = 0x00ff00;
	int Rect::blue = 0x0000ff;
	int Rect::black = 0x000000;
	int Rect::white = 0xffffff;
#else
	int Rect::red = 0x0000ff;
	int Rect::green = 0x00ff00;
	int Rect::blue = 0xff0000;
	int Rect::black = 0xffffff;
	int Rect::white = 0x000000;
#endif

Rect::Rect()
{
}

void Rect::setColor(int c)
{
	color = c;
	update();
}

int Rect::getColor() const
{
	return color;
}

void Rect::paint(SDL_Surface* surface)
{
	SDL_FillRect(surface, NULL, color);
}

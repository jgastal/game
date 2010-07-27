#include "rect.h"
#include <SDL.h>

Rect::Rect(Widget* parent): Widget(parent)
{
}

void Rect::setColor(SDL_Color c)
{
	color = c;
	update();
}

SDL_Color Rect::getColor() const
{
	return color;
}

void Rect::paint(SDL_Surface* surface)
{
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, color.r, color.g, color.b));
}

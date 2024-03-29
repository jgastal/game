#include "button.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

using namespace std;

namespace libwidget {

Button::Button(Widget* parent): Image(parent)
{
	font = NULL;
}

Button::~Button()
{
	if(font)
		TTF_CloseFont(font);
}

void Button::setText(string t)
{
	text = t;
	update();
}

void Button::setTextColor(SDL_Color c)
{
	textColor = c;
	update();
}

void Button::setBackgroundColor(SDL_Color c)
{
	bgColor = c;
	update();
}

void Button::setFont(string name)
{
	if(font)
		TTF_CloseFont(font);
	font = TTF_OpenFont(name.c_str(), fontSize);
	if(font)
		update();
	else
		cerr << "Error loading font: " << TTF_GetError() << endl;
}

void Button::setFontSize(int sz)
{
	fontSize = sz;
	update();
}

void Button::paint(SDL_Surface* surface)
{
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, bgColor.r, bgColor.g, bgColor.b));
	Image::paint(surface);
	if(text.empty())
		return;
	SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	SDL_Rect pos;
	pos.x = (surface->w - textSurface->w) / 2; //centralize
	pos.y = (surface->h - textSurface->h) / 2; //centralize
	SDL_BlitSurface(textSurface, NULL, surface, &pos);
}

}

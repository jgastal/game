#include "image.h"

#include <SDL_image.h>

Image::Image(Widget *parent) : Widget(parent)
{
	image = NULL;
}

Image::~Image()
{
	if(image)
		SDL_FreeSurface(image);
}

void Image::setImage(string i)
{
	if(image)
		SDL_FreeSurface(image);
	image = IMG_Load(i.c_str());
	update();
}

void Image::paint(SDL_Surface* surface)
{
	if(!image)
		return;
	SDL_BlitSurface(image, NULL, surface, NULL);
}

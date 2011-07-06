#include "image.h"

#include <SDL_image.h>

namespace libwidget {

Image::Image(Widget *parent) : Widget(parent), imgWidth(0), imgHeight(0), offX(0), offY(0)
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
	imgWidth = image->w;
	imgHeight = image->h;
	update();
	imageLoaded(i);
}

void Image::paint(SDL_Surface* surface)
{
	if(!image)
		return;
	SDL_Rect src = {offX, offY, imgWidth, imgHeight};
	SDL_BlitSurface(image, &src, surface, NULL);
}

int Image::getImgHeight() const
{
	return imgHeight;
}

int Image::getImgWidth() const
{
	return imgWidth;
}

void Image::onImageLoaded(stringSignal::Slot listener)
{
	imageLoaded.connect(listener);
}

}

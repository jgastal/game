#ifndef IMAGE_H
#define IMAGE_H

#include "widget.h"
#include "signal.hpp"
#include <string>

using namespace std;

namespace libwidget {

class Image : public Widget
{
	typedef Signal<string> stringSignal;

	public:
		Image(Widget *parent = 0);
		~Image();
		void setImage(string name);
		int getImgWidth() const;
		int getImgHeight() const;
		void onImageLoaded(stringSignal::Slot listener);

	protected:
		virtual void paint(SDL_Surface* surface);
		int offX, offY;

	private:
		SDL_Surface *image;
		int imgWidth, imgHeight;
		Signal<string> imageLoaded;
};

}

#endif // IMAGE_H

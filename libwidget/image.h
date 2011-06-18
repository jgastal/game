#ifndef IMAGE_H
#define IMAGE_H

#include "widget.h"
#include <string>

using namespace std;

namespace libwidget {

class Image : public Widget
{
	public:
		Image(Widget *parent = 0);
		~Image();
		void setImage(string name);

	protected:
		virtual void paint(SDL_Surface* surface);

	private:
		SDL_Surface *image;
};

}

#endif // IMAGE_H

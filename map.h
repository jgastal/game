#ifndef MAP_H
#define MAP_H

#include "image.h"

using namespace libwidget;

namespace libwidget {
	class Rect;
}

class Map : public Image
{
	public:
		Map();

	private:
		void haveImage(string str);
		void resized(int oldW, int oldY);
		void movePlayer(SDL_KeyboardEvent *ev);
		Rect *player;
		int width, height, imgWidth, imgHeight;
};

#endif // MAP_H

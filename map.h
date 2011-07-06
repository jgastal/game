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
		virtual void resize(int w, int h);

	private:
		void movePlayer(SDL_KeyboardEvent *ev);
		Rect *player;
		int width, height, imgWidth, imgHeight;
};

#endif // MAP_H

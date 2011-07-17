#include "map.h"

#include "rect.h"
#include "parser.h"
#include "value.h"

#define MIN_DIST 20

using namespace libwidget;


Map::Map(string file, int w, int h)
{
	player = new Rect(this);
	player->resize(10, 10);
	player->move(MIN_DIST, MIN_DIST);
	player->setColor(blue);

	pulpjson::Parser p(file.c_str());
	pulpjson::Object obj = p.getRootObject();
	setImage(obj["file"].asString());
	imgWidth = getImgWidth();
	imgHeight = getImgHeight();

	resize(w, h);
	width = w;
	height = h;

	onKeyPressed(bind(this, &Map::movePlayer));
}

void Map::movePlayer(SDL_KeyboardEvent* ev)
{
	SDL_Rect playerGeo = player->getGeometry();
	switch(ev->keysym.sym)
	{
		case SDLK_UP:
			if(playerGeo.y > 0)
				player->move(playerGeo.x, playerGeo.y -= 2);
			if(offY > 0 && playerGeo.y <= MIN_DIST)
				offY--;
			break;
		case SDLK_DOWN:
			if(playerGeo.y + playerGeo.h < height)
				player->move(playerGeo.x, playerGeo.y += 2);
			if(offY + height < imgHeight && playerGeo.y + playerGeo.h >= height - MIN_DIST)
				offY++;
			break;
		case SDLK_RIGHT:
			if(playerGeo.x + playerGeo.w < width)
				player->move(playerGeo.x += 2, playerGeo.y);
			if(offX + width < imgWidth && playerGeo.x + playerGeo.w >= width - MIN_DIST)
				offX++;
			break;
		case SDLK_LEFT:
			if(playerGeo.x > 0)
				player->move(playerGeo.x -= 2, playerGeo.y);
			if(offX > 0 && playerGeo.x <= MIN_DIST)
				offX--;
			break;
	}
}

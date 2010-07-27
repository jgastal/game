#include "widget.h"
#include "menu.h"
#include "map.h"
#include <button.h>

int main(int argc, char **argv)
{
	int width = Widget::getScreenWidth();
	int height = Widget::getScreenHeight();

	Menu *menu = new Menu();
	menu->resize(width / 5 < 200 ? 200 : width / 5, height);
	menu->move(width - menu->getGeometry().w, 0);
	Map *map = new Map();
	map->resize(width - menu->getGeometry().w, height);

	Button bt(menu);
	bt.setText("Button");
	bt.setImage("bt.png");
	bt.resize(150, 50);
	bt.move(25, 50);

	Widget::runEventLoop();
	delete menu;
	delete map;

	return 0;
}

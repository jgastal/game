#include "application.h"
#include "widget.h"
#include "menu.h"
#include "map.h"
#include "button.h"

using namespace libwidget;

void stop()
{
	Application::getInstance()->stop();
}

int main(int argc, char **argv)
{
	Application app(false, 800, 600);
	int width = app.getScreenWidth();
	int height = app.getScreenHeight();
	app.onCloseRequested(&stop);

	Menu *menu = new Menu();
	menu->resize(width / 5 < 200 ? 200 : width / 5, height);
	menu->move(width - menu->getGeometry().w, 0);
	Map *map = new Map();
	map->resize(width - menu->getGeometry().w, height);

	app.run();

	delete menu;
	delete map;

	return 0;
}

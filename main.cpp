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
	app.onCloseRequested(bind(&stop));

	Menu *menu = new Menu();
	menu->resize(width, 100);
	menu->move(0, height - 100);
	Map *map = new Map();
	map->setImage("res/grass.png");
	map->resize(width, height - 100);

	app.run();

	delete menu;
	delete map;

	return 0;
}

#include "menu.h"
#include "application.h"

using namespace libwidget;

Menu::Menu()
{
	status = true;
	setColor(blue);
	onClicked(bind(this, &Menu::changeColor));

	bt = new Rect(this);
	bt->setColor(white);
	bt->resize(150, 50);
	bt->move(25, 50);

	bt->onClicked(bind(this, &Menu::close));
}

void Menu::changeColor(SDL_MouseButtonEvent* event)
{
	status = !status;
	if(status)
		setColor(blue);
	else
		setColor(red);
}

void Menu::close(SDL_MouseButtonEvent *ev)
{
	Application::getInstance()->stop();
}

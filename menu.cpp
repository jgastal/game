#include "menu.h"
#include "application.h"
#include <boost/signal.hpp>
#include <boost/bind.hpp>

using namespace libwidget;

Menu::Menu()
{
	status = true;
	setColor(blue);
	onClicked(boost::bind(&Menu::changeColor, this, _1));

	bt = new Rect(this);
	bt->setColor(white);
	bt->resize(150, 50);
	bt->move(25, 50);

	bt->onClicked(boost::bind(&Menu::close, this, _1));
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

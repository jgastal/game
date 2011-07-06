#include "menu.h"
#include "application.h"

using namespace libwidget;

Menu::Menu()
{
	status = true;
	setColor(blue);
	onClicked(bind(this, &Menu::changeColor));

	bt = new Button(this);
	bt->setFontSize(20);
	bt->setFont("res/arial.ttf");
	bt->setText("Quit");
	bt->setBackgroundColor(white);
	bt->setTextColor(black);
	bt->resize(100, 50);
	bt->move(25, 25);

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

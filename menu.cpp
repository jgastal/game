#include "menu.h"
#include "application.h"

using namespace libwidget;

Menu::Menu()
{
	status = true;
	setColor(blue);
}

void Menu::processEvent(SDL_Event* event)
{
	if(event->type == SDL_QUIT)
		Application::getInstance()->stop();
	else
		libwidget::Widget::processEvent(event);
}

void Menu::leftClicked(SDL_MouseButtonEvent* event)
{
	status = !status;
	if(status)
		setColor(blue);
	else
		setColor(red);
}

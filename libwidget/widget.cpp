#include "widget.h"
#include <SDL.h>
#include <iostream>

#include "application.h"

using namespace std;

namespace libwidget {

Widget::Widget(Widget* parent)
{
	blockEvents = false;
	if(parent)
		parent->children.push_back(this);
	geometry = new SDL_Rect();

	Application *app = Application::getInstance();
	if(!parent) //only top level widgets receive events directly
		app->widgets.push_back(this);
	depth = app->getDepth();

	this->parent = parent;
	surface = NULL;
}

Widget::~Widget()
{
	delete geometry;
	if(surface)
		SDL_FreeSurface(surface);
	if(parent)
		parent->children.remove(this);
	else
		Application::getInstance()->widgets.remove(this);
	while(children.size())
	{
		Widget *w = children.back();
		children.remove(w);
		delete w;
	}
}

SDL_Rect Widget::getGeometry() const
{
	return *geometry;
}

list< Widget* > Widget::getChildren() const
{
	return children;
}

bool Widget::getBlockEvents() const
{
	return blockEvents;
}

void Widget::setBlockEvents(bool block)
{
	blockEvents = block;
}

void Widget::processEvent(SDL_Event* event)
{
	switch(event->type)
	{
		case SDL_MOUSEBUTTONUP:
			if(contains(event->button.x, event->button.y))
			{
				clicked(&(event->button));
				switch(event->button.button)
				{
					case SDL_BUTTON_LEFT:
						leftClicked(&(event->button));
						break;
					case SDL_BUTTON_RIGHT:
						rightClicked(&(event->button));
						break;
					case SDL_BUTTON_MIDDLE:
						middleClicked(&(event->button));
						break;
				}
			}
			break;
		case SDL_MOUSEMOTION:
			mouseMoved(&(event->motion));
			break;
		case SDL_KEYDOWN:
			keyEvent(&(event->key));
			break;
	}
	if(!blockEvents)
	{
		for(list<Widget*>::iterator it = children.begin(); it != children.end(); it++)
		{
			event->button.x -= geometry->x;
			event->button.y -= geometry->y;
			(*it)->processEvent(event);
		}
	}
}

void Widget::move(int x, int y)
{
	geometry->x = x;
	geometry->y = y;
	update();
}

void Widget::resize(int w, int h)
{
	if(w == geometry->w && h == geometry->h)
		return;
	geometry->w = w;
	geometry->h = h;
	SDL_FreeSurface(surface);
	surface = SDL_CreateRGBSurface(SDL_HWSURFACE, geometry->w, geometry->h, depth, 0, 0, 0, 0);
	update();
}

void Widget::update()
{
	if(geometry->w && geometry->h)
	{
		if(!surface)
			surface = SDL_CreateRGBSurface(SDL_HWSURFACE, geometry->w, geometry->h, depth, 0, 0, 0, 0);
		paint(surface);
	}
}

void Widget::render(SDL_Surface* target)
{
	//render all my children on me
	for(list<Widget*>::iterator it = children.begin(); it != children.end(); it++)
		(*it)->render(surface);
	SDL_Rect size = *geometry;
	size.x = size.y = 0;
	SDL_Rect t = *geometry;
	t.w = t.h = 0;
	SDL_BlitSurface(surface, &size, target, &t);
}

bool Widget::contains(int x, int y)
{
	if(x < geometry->x || x > geometry->x + geometry->w || y < geometry->y || y > geometry->y + geometry->h)
		return false;
	return true;
}

void Widget::onClicked(mouseSignal::Slot listener)
{
	return clicked.connect(listener);
}

void Widget::onLeftClicked(mouseSignal::Slot listener)
{
	return leftClicked.connect(listener);
}

void Widget::onRightClicked(mouseSignal::Slot listener)
{
	return rightClicked.connect(listener);
}

void Widget::onMiddleClicked(mouseSignal::Slot listener)
{
	return middleClicked.connect(listener);
}

void Widget::onKeyPressed(keySignal::Slot listener)
{
	return keyPressed.connect(listener);
}

}

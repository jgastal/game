#ifndef WIDGET_H
#define WIDGET_H

#include <list>
#include <SDL.h>
#include "signal.hpp"

/*
 * TODO:
 * 	- Does update need to update children?
 * 	- Render should be private
 * 	- Can we render less often?
 * 	- Clipping
 */

using namespace libsignal;

namespace libwidget {

static SDL_Color red = {0xff, 0, 0, 0};
static SDL_Color green = {0, 0xff, 0, 0};
static SDL_Color blue = {0, 0, 0xff, 0};
static SDL_Color black = {0, 0, 0, 0};
static SDL_Color white = {0xff, 0xff, 0xff, 0};

class Widget
{
	public:
		Widget(Widget *parent = 0);
		virtual ~Widget();
		SDL_Rect getGeometry() const;
		std::list<Widget*> getChildren() const;
		bool getBlockEvents() const;
		void setBlockEvents(bool block);
		bool contains(int x, int y);
		virtual void move(int x, int y);
		virtual void resize(int w, int h);
		void update();
		void render(SDL_Surface *target);
		virtual void processEvent(SDL_Event *event);

	protected:
		virtual void paint(SDL_Surface *surface) { };

	private:
		Widget *parent;
		std::list<Widget*> children;
		bool focus;
		bool blockEvents;
		int depth;
		SDL_Rect *geometry;
		SDL_Surface *surface;

		//signals
		CREATE_SIGNAL(clicked, onClicked, SDL_MouseButtonEvent*)
		CREATE_SIGNAL(leftClicked, onLeftClicked, SDL_MouseButtonEvent*)
		CREATE_SIGNAL(rightClicked, onRightClicked, SDL_MouseButtonEvent*)
		CREATE_SIGNAL(middleClicked, onMiddleClicked, SDL_MouseButtonEvent*)
		CREATE_SIGNAL(keyPressed, onKeyPressed, SDL_KeyboardEvent*)
		CREATE_SIGNAL(resized, onResized, int, int)
		CREATE_SIGNAL(moved, onMoved, int, int)
};

}

#endif // WIDGET_H

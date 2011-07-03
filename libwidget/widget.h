#ifndef WIDGET_H
#define WIDGET_H

#include <list>
#include <SDL.h>
#include "signal.hpp"

/*
 * TODO:
 * 	- Render should be private
 */

namespace libwidget {

static SDL_Color red = {0xff, 0, 0, 0};
static SDL_Color green = {0, 0xff, 0, 0};
static SDL_Color blue = {0, 0, 0xff, 0};
static SDL_Color black = {0, 0, 0, 0};
static SDL_Color white = {0xff, 0xff, 0xff, 0};

class Widget
{
	typedef Signal<SDL_MouseButtonEvent*> mouseSignal;
	typedef Signal<SDL_KeyboardEvent*> keySignal;

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

		void onClicked(mouseSignal::Slot listener);
		void onLeftClicked(mouseSignal::Slot listener);
		void onRightClicked(mouseSignal::Slot listener);
		void onMiddleClicked(mouseSignal::Slot listener);
		void onKeyPressed(keySignal::Slot listener);

	protected:
		virtual void paint(SDL_Surface *surface) { };

	private:
		Widget *parent;
		std::list<Widget*> children;
		bool focus;
		bool blockEvents;
		bool updated;
		int depth;
		SDL_Rect *geometry;
		SDL_Surface *surface;

		//signals
		Signal<SDL_MouseButtonEvent*> clicked;
		Signal<SDL_MouseButtonEvent*> leftClicked;
		Signal<SDL_MouseButtonEvent*> rightClicked;
		Signal<SDL_MouseButtonEvent*> middleClicked;
		Signal<SDL_KeyboardEvent*> keyPressed;
};

}

#endif // WIDGET_H

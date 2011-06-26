#ifndef WIDGET_H
#define WIDGET_H

#include <list>
#include <SDL.h>
#include <boost/signal.hpp>

/*
 * TODO:
 * 	- Does update need to update children?
 * 	- Render should be private
 * 	- Render only if updated
 * 	- Clipping
 */

namespace libwidget {

class Widget
{
	typedef boost::signal<void(SDL_MouseButtonEvent*)> mouseSignal;
	typedef boost::signal<void(SDL_KeyboardEvent*)> keySignal;

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

		boost::signals::connection onClicked(mouseSignal::slot_function_type listener);
		boost::signals::connection onLeftClicked(mouseSignal::slot_function_type listener);
		boost::signals::connection onRightClicked(mouseSignal::slot_function_type listener);
		boost::signals::connection onMiddleClicked(mouseSignal::slot_function_type listener);
		boost::signals::connection onKeyPressed(keySignal::slot_function_type listener);

		static SDL_Color red;
		static SDL_Color blue;
		static SDL_Color green;
		static SDL_Color black;
		static SDL_Color white;

	protected:
		virtual void paint(SDL_Surface *surface) { };
		virtual void mouseMoved(SDL_MouseMotionEvent *event) { };
		virtual void keyEvent(SDL_KeyboardEvent *event) { };

	private:
		Widget *parent;
		std::list<Widget*> children;
		bool focus;
		bool blockEvents;
		int depth;
		SDL_Rect *geometry;
		SDL_Surface *surface;

		//signals
		boost::signal<void(SDL_MouseButtonEvent*)> clicked;
		boost::signal<void(SDL_MouseButtonEvent*)> leftClicked;
		boost::signal<void(SDL_MouseButtonEvent*)> rightClicked;
		boost::signal<void(SDL_MouseButtonEvent*)> middleClicked;
		boost::signal<void(SDL_KeyboardEvent*)> keyPressed;
};

}

#endif // WIDGET_H

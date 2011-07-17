#ifndef APPLICATION_H
#define APPLICATION_H

#include <list>
#include "signal.hpp"
#include "widget.h"

namespace libwidget
{

/*
 * TODO:
 * 	- Remove friends
 */
class Application
{
	public:
		Application(bool fullscreen = true, int w = 800, int h = 600);
		virtual ~Application();
		void run();
		void stop();
		int getScreenWidth();
		int getScreenHeight();
		int getDepth();
		static Application *getInstance();

	private:
		friend Widget::Widget(Widget *parent);
		friend Widget::~Widget();
		std::list<Widget*> widgets;
		bool running;
		int depth;
		static void exiting();
		static Application *instance;
		CREATE_SIGNAL(closeRequested, onCloseRequested);
};

}

#endif // APPLICATION_H

#ifndef APPLICATION_H
#define APPLICATION_H

#include <list>
#include "widget.h"

namespace libwidget
{

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
};

}

#endif // APPLICATION_H

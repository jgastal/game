#ifndef APPLICATION_H
#define APPLICATION_H

#include <list>
#include <boost/signal.hpp>
#include "widget.h"

namespace libwidget
{

class Application
{
	typedef boost::signal<void()> closeSignal;
	public:
		Application(bool fullscreen = true, int w = 800, int h = 600);
		virtual ~Application();
		void run();
		void stop();
		int getScreenWidth();
		int getScreenHeight();
		int getDepth();
		static Application *getInstance();
		void onCloseRequested(closeSignal::slot_function_type listener);

	private:
		friend Widget::Widget(Widget *parent);
		friend Widget::~Widget();
		std::list<Widget*> widgets;
		bool running;
		int depth;
		static void exiting();
		static Application *instance;
		boost::signal<void()> closeRequested;
};

}

#endif // APPLICATION_H

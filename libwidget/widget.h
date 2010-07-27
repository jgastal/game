#ifndef WIDGET_H
#define WIDGET_H

#include <list>
#include <SDL.h>

class Widget
{
	public:
		Widget(Widget *parent = 0);
		~Widget();
		SDL_Rect getGeometry() const;
		std::list<Widget*> getChildren() const;
		bool getBlockEvents() const;
		void setBlockEvents(bool block);
		bool contains(int x, int y);
		virtual void move(int x, int y);
		virtual void resize(int w, int h);
		void update();
		void render(SDL_Surface *target);

		static void init();
		static void runEventLoop();
		static int getScreenWidth();
		static int getScreenHeight();

		static SDL_Color red;
		static SDL_Color blue;
		static SDL_Color green;
		static SDL_Color black;
		static SDL_Color white;

	protected:
		virtual void processEvent(SDL_Event *event);
		virtual void paint(SDL_Surface *surface) { };
		virtual void clicked(SDL_MouseButtonEvent *event) { focus = true; };
		virtual void leftClicked(SDL_MouseButtonEvent *event) { };
		virtual void rightClicked(SDL_MouseButtonEvent *event) { };
		virtual void middleClicked(SDL_MouseButtonEvent *event) { };
		virtual void mouseMoved(SDL_MouseMotionEvent *event) { };
		virtual void keyEvent(SDL_KeyboardEvent *event) { };

	private:
		void addChild(Widget *child);
		Widget *parent;
		std::list<Widget*> children;
		bool focus;
		bool blockEvents;
		SDL_Rect *geometry;
		SDL_Surface *surface;

		static int depth;
		static bool inited;
		static void cleanUp();
};

void runEventLoop();

#endif // WIDGET_H

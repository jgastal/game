#ifndef WIDGET_H
#define WIDGET_H

#include <list>

struct SDL_Surface;
struct SDL_KeyboardEvent;
struct SDL_MouseMotionEvent;
struct SDL_Rect;
struct SDL_MouseButtonEvent;
union SDL_Event;

class Widget
{
	public:
		Widget(Widget *parent = 0);
		~Widget();
		SDL_Rect getGeometry() const;
		std::list<Widget*> getChildren() const;
		void setBlockEvents(bool block);
		bool contains(int x, int y);
		virtual void processEvent(SDL_Event *event);
		virtual void move(int x, int y);
		virtual void resize(int w, int h);
		void update();
		void render(SDL_Surface *target);

		static void initVideo();
		static void runEventLoop();

	protected:
		virtual void paint(SDL_Surface *surface) { };
		virtual void clicked(SDL_MouseButtonEvent *event) { focus = true; };
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

		static void cleanUp();
};

void runEventLoop();

#endif // WIDGET_H

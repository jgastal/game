#include "widget.h"
#include <SDL.h>
#include <iostream>

//Global list of all top level widgets
static std::list<Widget*> __widgetList;
int Widget::depth = 0;

Widget::Widget(Widget* parent)
{
	blockEvents = false;
	if(parent)
		parent->addChild(this);
	geometry = new SDL_Rect();
	if(!parent) //only top level widgets receive events directly
		__widgetList.push_back(this);

	if(!depth)
		depth = SDL_GetVideoInfo()->vfmt->BitsPerPixel;
	surface = NULL;
}

Widget::~Widget()
{
	delete geometry;
}

SDL_Rect Widget::getGeometry() const
{
	return *geometry;
}

std::list< Widget* > Widget::getChildren() const
{
	return children;
}

void Widget::setBlockEvents(bool block)
{
	blockEvents = block;
}

void Widget::processEvent(SDL_Event* event)
{
	if(!blockEvents)
	{
		for(std::list<Widget*>::iterator it = children.begin(); it != children.end(); it++)
			(*it)->processEvent(event);
	}
	switch(event->type)
	{
		case SDL_MOUSEBUTTONUP:
			if(contains(event->button.x, event->button.y))
				clicked(&(event->button));
			break;
		case SDL_MOUSEMOTION:
			mouseMoved(&(event->motion));
			break;
		case SDL_KEYDOWN:
			keyEvent(&(event->key));
			break;
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
	for(std::list<Widget*>::iterator it = children.begin(); it != children.end(); it++)
		(*it)->render(surface);
	SDL_Rect *size = (SDL_Rect*)calloc(sizeof(SDL_Rect), 1);
	size->w = geometry->w;
	size->h = geometry->h;
	SDL_BlitSurface(surface, size, target, &getGeometry());
	free(size);
}

bool Widget::contains(int x, int y)
{
	if(x < geometry->x || x > geometry->x + geometry->w)
		return false;
	if(y < geometry->y || y > geometry->y + geometry->h)
		return false;
	return true;
}

void Widget::addChild(Widget* child)
{
	children.push_back(child);
}

//NOT part of Widget class but here because widget does all event handling
void Widget::runEventLoop()
{
	while(true)
	{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{  /* Loop until there are no events left on the queue */
			if(event.type == SDL_QUIT) //quit loop on alt+f4
				return;
			for(std::list<Widget*>::iterator it = __widgetList.begin(); it != __widgetList.end(); it++)
				(*it)->processEvent(&event);
		}
		//when do I render?! always is overkill!
		for(std::list<Widget*>::iterator it = __widgetList.begin(); it != __widgetList.end(); it++)
			(*it)->render(SDL_GetVideoSurface());;
		//done processing events, repaint screen
		SDL_Flip(SDL_GetVideoSurface());
		SDL_Delay(0);
	}
}

void Widget::initVideo()
{
#ifndef DEBUG
	Uint32 displayFlags = SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_ANYFORMAT | SDL_FULLSCREEN;
#else
	Uint32 displayFlags = SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_ANYFORMAT;
#endif

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTTHREAD) < 0)
	{
		std::cerr << "Failed to init SDL: " << SDL_GetError();
		exit(-1);
	}
	atexit(SDL_Quit);

	const SDL_VideoInfo *info = SDL_GetVideoInfo();
	SDL_Rect **modes = SDL_ListModes(info->vfmt, displayFlags);
	if(modes == (SDL_Rect**)0)
	{
		displayFlags |= !SDL_HWSURFACE;
		modes = SDL_ListModes(info->vfmt, displayFlags);
		if(modes == (SDL_Rect**)0)
		{
			std::cerr << "No video modes available.\n";
			exit(-1);
		}
	}

	int width = 0, height = 0;
	if (modes == (SDL_Rect**)-1)
	{ //no restriction on video mode, use current resolution
		width = info->current_w;
		height = info->current_h;
	}
	else
	{ //get highest available resolution(as measured by having greatest width)
		for(int i = 0; modes[i]; i++)
		{
			if(modes[i]->w >= width)
			{
				width = modes[i]->w;
				height = modes[i]->h;
			}
		}
	}
#ifdef DEBUG
	width = 800;
	height = 600;
#endif

	if(SDL_SetVideoMode(width, height, info->vfmt->BitsPerPixel, displayFlags))
		atexit(Widget::cleanUp);
}

void Widget::cleanUp()
{
	SDL_FreeSurface(SDL_GetVideoSurface());
}

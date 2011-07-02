#include "application.h"

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

namespace libwidget {

Application *Application::instance = NULL;

Application::Application(bool fullscreen, int w, int h)
{
	instance = this;

	Uint32 displayFlags = SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_ANYFORMAT;
	if(fullscreen)
		displayFlags |= SDL_FULLSCREEN;

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTTHREAD) < 0)
	{
		cerr << "Failed to init SDL: " << SDL_GetError();
		exit(-1);
	}

	const SDL_VideoInfo *info = SDL_GetVideoInfo();
	SDL_Rect **modes = SDL_ListModes(info->vfmt, displayFlags);
	if(modes == (SDL_Rect**)0)
	{
		displayFlags |= !SDL_HWSURFACE;
		modes = SDL_ListModes(info->vfmt, displayFlags);
		if(modes == (SDL_Rect**)0)
		{
			cerr << "No video modes available.\n";
			exit(-1);
		}
	}

	int width = 0, height = 0;
	if(fullscreen)
	{
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
	}
	else
	{
		width = w;
		height = h;
	}

	depth = info->vfmt->BitsPerPixel;
	if(SDL_SetVideoMode(width, height, depth, displayFlags))
		atexit(Application::exiting);
	else
	{
		cerr << "Failed to set video mode: " << width << "x" << height << " " << depth << "bpp\n";
		exit(-1);
	}

	if(TTF_Init())
	{
		cerr << "Failed to initialize SDL_ttf\n";
		return;
	}
}

Application::~Application()
{
	SDL_FreeSurface(SDL_GetVideoSurface());
#ifdef LIBWIDGET_AUTO_FREE
	while(widgets.size())
		widgets.pop_front();
#else
	if(widgets.size() > 0)
		cerr << "SPANK SPANK SPANK\nSome widgets are still live.\n";
#endif
	TTF_Quit();
	SDL_Quit();
}

void Application::exiting()
{
	SDL_FreeSurface(SDL_GetVideoSurface());
}

int Application::getScreenWidth()
{
	return SDL_GetVideoSurface()->w;
}

int Application::getScreenHeight()
{
	return SDL_GetVideoSurface()->h;
}

void Application::run()
{
	running = true;
	while(running)
	{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{  // Loop until there are no events left on the queue
			if(event.type == SDL_QUIT)
				closeRequested();
			for(list<Widget*>::iterator it = widgets.begin(); it != widgets.end(); it++)
				(*it)->processEvent(&event);
		}
		//when do I render?! always is overkill!
		for(list<Widget*>::iterator it = widgets.begin(); it != widgets.end(); it++)
			(*it)->render(SDL_GetVideoSurface());;
		//done processing events, repaint screen
		SDL_Flip(SDL_GetVideoSurface());
		SDL_Delay(0);
	}
}

void Application::stop()
{
	running = false;
}

Application* Application::getInstance()
{
	return instance;
}

int Application::getDepth()
{
	return depth;
}

void Application::onCloseRequested(Signal::FuncPtr listener)
{
	closeRequested.connect(listener);
}

}

#ifndef BUTTON_H
#define BUTTON_H

#include "widget.h"
#include <string>

using namespace std;

typedef struct _TTF_Font TTF_Font;

class Button : public Widget
{
	public:
		Button(Widget* parent = 0);
		~Button();
		void setText(string t);
		void setImage(string i);
		void setColor(SDL_Color c);
		void setFont(string name);
		void setFontSize(int sz);

	protected:
		virtual void paint(SDL_Surface* surface);
		virtual void leftClicked(SDL_MouseButtonEvent* event);

	private:
		string text;
		SDL_Color color;
		SDL_Surface *image;
		TTF_Font *font;
		int fontSize;
};

#endif // BUTTON_H

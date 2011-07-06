#ifndef BUTTON_H
#define BUTTON_H

#include "image.h"
#include "rect.h"
#include <string>

using namespace std;

typedef struct _TTF_Font TTF_Font;

namespace libwidget {

class Button : public Image
{
	public:
		Button(Widget* parent = 0);
		~Button();
		void setText(string t);
		void setTextColor(SDL_Color c);
		void setBackgroundColor(SDL_Color c);
		void setFont(string name);
		void setFontSize(int sz);

	protected:
		virtual void paint(SDL_Surface* surface);

	private:
		string text;
		SDL_Color bgColor;
		SDL_Color textColor;
		TTF_Font *font;
		int fontSize;
};

}

#endif // BUTTON_H

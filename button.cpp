#include "button.hpp"

Button :: Button(int x_, int y_, int width_, int height_, RGB colour_, int xText_, int yText_, std::string lable_, std::string font_, int fontSize_)
{
	x = x_;
	y = y_;
	width = width_;
	height = height_;
	colour = colour_;
	xText = xText_;
	yText = yText_;
	lable = lable_;
	font = font_;
	fontSize = fontSize_;
}

void Button :: draw()
{
	win->fill_rect(x, y, width, height, colour);
	win->show_text(lable , xText , yText, WHITE, font, fontSize);
}

void Button :: setWindow(Window* win_)
{
	win = win_;
}

void Button :: choose()
{
	win->draw_rect(x - 10, y - 10, width + 20, height + 20, BLACK);
}
#include "src/rsdl.hpp"
#include <string>
#define FONT_FREESANS "FreeSans.ttf"

class Button {
private:
	int x, y, width , height , xText, yText, fontSize;
	std::string font , lable;
	RGB colour;
	Window* win;
public:
	Button(int x_ = 0, int y_ = 0, int width_ = 0, int height_ = 0, RGB colour_ = WHITE , int xText_ = 0, int yText_ = 0 , std::string lable_ = "", std::string font_ = "", int fontSize_ = 0);
	void draw();
	void setWindow(Window*);
	void choose();
};
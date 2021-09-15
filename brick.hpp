#include "src/rsdl.hpp"
#define GAME_BOARD_X 75
#define GAME_BOARD_Y 135
#define BRICK_WIDTH 60
#define BRICK_HEIGHT 40
#define FONT_FREESANS "FreeSans.ttf"
#define MARGIN_X 20
#define MARGIN_Y 15
#define BRICK_DISTANCE 5
#include <string>

class Brick {
private:

	float x, y;
	Window* win;
	int resistance;
	bool isBomb;
public:
	void draw();
	void setWindow(Window*);
	void setXY(float , float);
	bool exist;
	void exists(bool event);
	bool isExist();
	void writeResistance();
	void setResistance(int);
	int getResistance();
	void setBomb(bool);
	bool itIsBomb();
};
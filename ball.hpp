#include <cmath>
#include "src/rsdl.hpp"

#define GAME_BOARD_X 75
#define GAME_BOARD_Y 135
#define GAME_BOARD_WIDTH 350
#define GAME_BOARD_HEIGHT 415
#define BALL_PICTURE "Assets/Assets/ball.png"
#define RIGHT 79
#define LEFT 80
#define BALL_SPEED 15
#define ESC 27
#define SPACE 32
#define ENTER 13
#define P_NUMBER 3.14
#define DELAY_TIME 40

class Ball {
private:
	Window* win;
	int x, y;
	float vx, vy, radius;
	Event lastEvent;
public:
	void draw();
	void reflectFromWall();
	void setAngle();
	void move();
	void setWindow(Window*);
	Ball(int x_ = 0, int y_ = 0, float radius_ = 0);
	void deleteBall();
	int getY();
	float getRadius();
	void setV(float);
	int getX();
	void reflectFromBrick(std::string);
	float getVx();
	float getVy();

};
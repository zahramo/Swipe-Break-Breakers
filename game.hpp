#include "ball.hpp"
#include "user.hpp"
#include "brick.hpp"

#include <vector>
#include <ctime>
#include <string>

#define FONT_FREESANS "FreeSans.ttf"
#define BACKGROUND "star.jpg"
#define ENTER 13
#define P_NUMBER 3.14
#define ARROW_PICTURE "arrow.png"
#define BALL_PICTURE "Assets/Assets/ball.png"
#define BRICK_COLUMNS 5
#define BRICK_ROWS 8

class Game {
private:
	Window* win;
	User player;
	float angle ;
	Event lastEvent;
	std::vector<Ball> balls;
	bool exit, space , right , left ;
	Brick bricks[BRICK_ROWS][BRICK_COLUMNS];
	int level;
	int score;
public:
	Game() {angle = P_NUMBER / 2; score = 0;};
	void setWindow(Window*);
	void load();
	void handleLastEvent();
	void draw(Ball ball);
	void setAngle(char);
	void moveBall(Ball);
	void moveBalls();
	bool checkBallPosition(Ball);
	void drawBricks();
	void handleBricksExistence();
	void moveBricks();
	void setPossibility();
	void reflectFromBricks(Ball &ball);
	void setPlayer(User&);
	int getScore();
	void setBombPossibility();
	void destroyBricks(int, int);
	void destroy(std::string , int, int, Ball& ball);
};
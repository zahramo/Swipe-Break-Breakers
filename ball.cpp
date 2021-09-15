#include "ball.hpp"

void Ball :: setV(float angle)
{
	vx = BALL_SPEED * cos(angle) * (-1);
	vy = BALL_SPEED * sin(angle) * (-1);
}
int  Ball :: getY()
{
	return y;
}

int Ball :: getX()
{
	return x;
}

float Ball :: getRadius()
{
	return radius;
}

void Ball :: draw()
{
	if ((x + radius) > (GAME_BOARD_X + GAME_BOARD_WIDTH))
	{
		x = GAME_BOARD_WIDTH + GAME_BOARD_X - radius;
	}
	if ((x - radius) < GAME_BOARD_X)
	{
		x = GAME_BOARD_X + radius;
	}
	if ((y - radius) < GAME_BOARD_Y)
	{
		y = GAME_BOARD_Y + radius;
	}
	win->draw_png(BALL_PICTURE , x - radius , y - radius , 2 * radius , 2 * radius);
}

void Ball :: setWindow(Window* win_)
{
	win = win_;
}

Ball :: Ball(int x_, int y_, float radius_)
{
	x = x_;
	y = y_;
	radius = radius_;
}

void Ball :: move()
{
	reflectFromWall();

	x = x + vx;
	y = y + vy;
	Delay(DELAY_TIME);
}

void Ball :: reflectFromWall()
{
	if (x + radius >= GAME_BOARD_X + GAME_BOARD_WIDTH || x - radius <= GAME_BOARD_X)
	{
		vx = -vx;
	}
	if (y - radius <= GAME_BOARD_Y)
	{
		vy = -vy;
	}
}

void Ball :: reflectFromBrick(std::string position)
{
	if (position == "corner")
	{
		vx = -vx;
		vy = -vy;
	}

	if (position == "leftRight")
	{
		vx = -vx;
	}

	if (position == "upDown")
	{
		vy = -vy;
	}
}

float Ball :: getVx()
{
	return vx;
}

float Ball :: getVy()
{
	return vy;
}
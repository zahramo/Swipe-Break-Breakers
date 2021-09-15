#include "brick.hpp"

void Brick :: draw()
{
	if (isBomb == true)
	{
		win->fill_rect(MARGIN_X + x * BRICK_WIDTH + GAME_BOARD_X + (x - 1) * BRICK_DISTANCE , MARGIN_Y + y * BRICK_HEIGHT + (y - 1) * BRICK_DISTANCE + GAME_BOARD_Y, BRICK_WIDTH, BRICK_HEIGHT, RGB(0, 0, 0));
	}
	else if (255 - 20 * resistance >= 0)
	{
		win->fill_rect(MARGIN_X + x * BRICK_WIDTH + GAME_BOARD_X + (x - 1) * BRICK_DISTANCE , MARGIN_Y + y * BRICK_HEIGHT + (y - 1) * BRICK_DISTANCE + GAME_BOARD_Y, BRICK_WIDTH, BRICK_HEIGHT, RGB(255 - 20 * resistance, 0, 0));
	}
	else
	{
		win->fill_rect(MARGIN_X + x * BRICK_WIDTH + GAME_BOARD_X + (x - 1) * BRICK_DISTANCE , MARGIN_Y + y * BRICK_HEIGHT + (y - 1) * BRICK_DISTANCE + GAME_BOARD_Y, BRICK_WIDTH, BRICK_HEIGHT, RGB(0, (-1) * (255 - 20 * resistance), 0));
	}

	writeResistance();

}

void Brick :: setWindow(Window* win_)
{
	win = win_;
}

void Brick :: setXY(float x_, float y_)
{
	x = x_;
	y = y_;
}

void Brick :: exists(bool event)
{
	exist = event;
}

bool Brick :: isExist()
{
	return exist;
}

void Brick :: writeResistance()
{
	if (isBomb)
	{
		win->show_text( " " , MARGIN_X + x * BRICK_WIDTH + GAME_BOARD_X + (x - 1) * BRICK_DISTANCE + BRICK_WIDTH / 2 - 4 ,  MARGIN_Y + y * BRICK_HEIGHT + (y - 1) * BRICK_DISTANCE + GAME_BOARD_Y + BRICK_HEIGHT / 2 , WHITE , FONT_FREESANS , 14 );
	}
	else {
		win->show_text( std::to_string(resistance) , MARGIN_X + x * BRICK_WIDTH + GAME_BOARD_X + (x - 1) * BRICK_DISTANCE + BRICK_WIDTH / 2 - 4 ,  MARGIN_Y + y * BRICK_HEIGHT + (y - 1) * BRICK_DISTANCE + GAME_BOARD_Y + BRICK_HEIGHT / 2 , WHITE , FONT_FREESANS , 14 );
	}
}

void Brick :: setResistance(int resistance_)
{
	resistance = resistance_;
}

int Brick :: getResistance()
{
	return resistance;
}

void Brick :: setBomb(bool state)
{
	isBomb = state;
}

bool Brick :: itIsBomb()
{
	return isBomb;
}
#include "game.hpp"
using namespace std;

void Game :: setWindow(Window* win_)
{
	win = win_;
}

void Game::draw(Ball ball)
{
	win->clear();
	win->draw_bg(BACKGROUND, 0, 0);
	win->fill_rect(25, 25, 450, 100, WHITE);
	win->draw_rect(25, 25, 450, 100, BLACK);
	win->fill_rect(75, 135, 350, 415, WHITE);
	win->draw_rect(75, 135, 350, 415, BLACK);
	win->show_text("Name :", 40, 40, BLACK, FONT_FREESANS, 14);
	win->show_text("Score :", 40, 70, BLACK, FONT_FREESANS, 14);
	win->show_text(to_string(score), 200, 70, BLACK, FONT_FREESANS, 14);
	win->show_text("Record :", 40, 100, BLACK, FONT_FREESANS, 14);
	drawBricks();
	ball.draw();
	if (!space)
	{
		win->draw_png(ARROW_PICTURE, ball.getX() - ball.getRadius(), ball.getY() - 3 * ball.getRadius(), 20, 60, (180 * angle) / P_NUMBER - 90);
		Delay(40);
	}
	win->update_screen();
}

void Game :: load()
{
	srand(time(0));
	handleBricksExistence();
	for (int i = 0 ; i < balls.size(); i++)
	{
		balls[i].setWindow(win);
	}
	level = 1;
	int curLevel = level;
	exit = false;
	space = false;
	score = 0;
	angle = P_NUMBER / 2;

	Ball ball;
	ball = Ball(250, 530, 10);
	balls.push_back(ball);
	while (!exit)
	{
		if (curLevel == level)
		{
			setPossibility();
			moveBricks();
			curLevel++;
		}

		space = false;
		for ( int i = 0 ; i < balls.size(); i++)
		{
			balls[i] = Ball(250, 530, 10);
		}
		draw(ball);
		ball.draw();
		lastEvent = win->pollForEvent();
		if (lastEvent.type() == KEY_PRESS)
		{
			if (lastEvent.pressedKey() == ENTER)
			{
				exit = true;
			}
			if (lastEvent.pressedKey() == SPACE )
			{
				space = true;
				moveBalls();
				level++;
				score++;
			}
			if (lastEvent.pressedKey() == RIGHT || lastEvent.pressedKey() == LEFT )
			{
				setAngle(lastEvent.pressedKey());
				draw(ball);
			}
		}

	}
}

void Game :: setAngle(char event)
{
	if (event == RIGHT && angle > 0)
	{
		angle = angle + (P_NUMBER / 90);
	}
	if (event == LEFT && angle < P_NUMBER)
	{
		angle = angle - (P_NUMBER / 90);
	}
}

void Game :: moveBalls()
{
	for (int j = 0 ; j < balls.size(); j++)
	{
		balls[j].setV(angle);
	}
	angle = P_NUMBER / 2;
	bool quit = false;
	while (!quit)
	{
		quit = 1;
		for (int i = 0 ; i < balls.size() ; i++)
		{
			if (checkBallPosition(balls[i]))
			{
				quit = 0;
				reflectFromBricks(balls[i]);
				balls[i].move();
				draw(balls[i]);
			}
		}
	}
}

bool Game :: checkBallPosition(Ball ball)
{
	if (ball.getY() + ball.getRadius() >= GAME_BOARD_Y + GAME_BOARD_HEIGHT )
	{
		return false;
	}
	return true;
}

void Game :: drawBricks()
{

	for (int i = 0 ; i < BRICK_ROWS; i++)
	{
		for (int j = 0 ; j < BRICK_COLUMNS ; j++)
		{
			if (bricks[i][j].isExist() == true)
			{
				bricks[i][j].setXY(j, i);
				bricks[i][j].setWindow(win);
				bricks[i][j].draw();
			}
		}

	}
}

void Game :: setPossibility()
{
	int rand1 = 0, rand2 = 0;
	if (level % 5 == 0 || level % 5 == 1 || level % 5 == 2)
	{
		while (rand1 == rand2)
		{
			rand1 = rand() % 5;
			rand2 = rand() % 5;
		}
		bricks[0][rand1].exists(true);
		bricks[0][rand1].setResistance(level);
		bricks[0][rand2].exists(true);
		bricks[0][rand2].setResistance(level);
	}
	if (level % 5 == 3)
	{
		rand1 = rand() % 5;
		bricks[0][rand1].exists(true);
		bricks[0][rand1].setResistance(level);
	}
	if (level % 5 == 4)
	{
		rand1 = rand() % 5;
		for (int i = 0 ; i < BRICK_COLUMNS ; i++)
		{
			if (i != rand1)
			{
				bricks[0][i].exists(true);
				bricks[0][i].setResistance(level);
			}
		}
	}
	setBombPossibility();
}

void Game :: handleBricksExistence()
{
	for (int i = 0 ; i < BRICK_ROWS ; i++)
	{
		for (int j = 0 ; j < BRICK_COLUMNS ; j++)
		{
			bricks[i][j].exists(false);
			bricks[i][j].setBomb(false);
		}
	}
}

void Game :: moveBricks()
{
	for (int i = 0 ; i < BRICK_COLUMNS ; i++)
	{
		if (bricks[BRICK_ROWS - 1][i].isExist() == true)
		{
			exit = true;
			return;
		}
	}
	for (int i = BRICK_ROWS - 2 ; i >= 0 ; i--)
	{
		for (int j = 0 ; j < BRICK_COLUMNS ; j++)
		{
			if (bricks[i][j].isExist() == true)
			{
				bricks[i][j].exists(false);
				if (bricks[i][j].itIsBomb() == true)
				{
					bricks[i][j].setBomb(false);
					bricks[i + 1][j].setBomb(true);
				}
				bricks[i + 1][j].exists(true);
				bricks[i + 1][j].setResistance(bricks[i][j].getResistance());

			}
		}
	}
}

void Game :: reflectFromBricks(Ball &ball)
{
	float bricksLeftUpCornerX , bricksLeftUpCornerY  , bricksRightUpCornerX , bricksRightUpCornerY , bricksLeftDownCornerX  , bricksLeftDownCornerY  , bricksRightDownCornerY  , bricksRightDownCornerX  ;

	for (int i = 0 ; i < BRICK_ROWS ; i++)
	{
		for (int j = 0 ; j < BRICK_ROWS ; j++)
		{
			if (bricks[i][j].isExist() == true)
			{
				bricksLeftUpCornerX = MARGIN_X + j * BRICK_WIDTH + GAME_BOARD_X + (j - 1) * BRICK_DISTANCE,
				bricksLeftUpCornerY = MARGIN_Y + i * BRICK_HEIGHT + (i - 1) * BRICK_DISTANCE + GAME_BOARD_Y,
				bricksRightUpCornerX = MARGIN_X + j * BRICK_WIDTH + GAME_BOARD_X + (j - 1) * BRICK_DISTANCE + BRICK_WIDTH,
				bricksRightUpCornerY = MARGIN_Y + i * BRICK_HEIGHT + (i - 1) * BRICK_DISTANCE + GAME_BOARD_Y ,
				bricksLeftDownCornerX = MARGIN_X + j * BRICK_WIDTH + GAME_BOARD_X + (j - 1) * BRICK_DISTANCE ,
				bricksLeftDownCornerY = MARGIN_Y + i * BRICK_HEIGHT + (i - 1) * BRICK_DISTANCE + GAME_BOARD_Y + BRICK_HEIGHT ,
				bricksRightDownCornerY = MARGIN_Y + i * BRICK_HEIGHT + (i - 1) * BRICK_DISTANCE + GAME_BOARD_Y + BRICK_HEIGHT ,
				bricksRightDownCornerX = MARGIN_X + j * BRICK_WIDTH + GAME_BOARD_X + (j - 1) * BRICK_DISTANCE + BRICK_WIDTH;

				if ((ball.getX() + ball.getRadius() >= bricksLeftUpCornerX && ball.getX() + ball.getRadius() <= bricksLeftUpCornerX + BRICK_WIDTH / 6 && (ball.getY() < bricksLeftDownCornerY && ball.getY() > bricksLeftUpCornerY) && ball.getVx() <= 0) ||
				        (ball.getX() - ball.getRadius() <= bricksRightUpCornerX && ball.getX() - ball.getRadius() >= bricksRightUpCornerX - BRICK_WIDTH / 6 && (ball.getY() < bricksLeftDownCornerY && ball.getY() > bricksLeftUpCornerY) && ball.getVx() > 0 ))
				{
					destroy("leftRight", i, j , ball);
				}
				if ((ball.getY() + ball.getRadius() >= bricksLeftUpCornerY && ball.getY() + ball.getRadius() <= bricksLeftUpCornerY + BRICK_HEIGHT / 4 && (ball.getX() < bricksRightUpCornerX && ball.getX() > bricksLeftUpCornerX) && ball.getVy() >= 0) ||
				        (ball.getY() - ball.getRadius() <= bricksLeftDownCornerY && ball.getY() - ball.getRadius() >= bricksLeftDownCornerY - BRICK_HEIGHT / 4  && (ball.getX() < bricksRightUpCornerX && ball.getX()  > bricksLeftUpCornerX)) && ball.getVy() < 0)
				{
					destroy("upDown", i, j , ball);
				}
			}

		}
	}
}

void Game :: destroy(std::string state , int i , int j , Ball& ball)
{
	if (bricks[i][j].itIsBomb() == true)
	{
		destroyBricks(i, j);
		bricks[i][j].exists(false);
		ball.reflectFromBrick(state);

	}
	else
	{
		if (bricks[i][j].getResistance() == 1)
		{
			bricks[i][j].exists(false);
		}

		int r = bricks[i][j].getResistance();
		bricks[i][j].setResistance(r - 1);
		ball.reflectFromBrick(state);

	}

}

void Game :: setPlayer(User& player_)
{
	player = player_;
}

int Game :: getScore()
{
	return score;
}

void Game :: setBombPossibility()
{
	for (int j = 0 ; j < BRICK_COLUMNS ; j++)
	{
		if (bricks[0][j].isExist() == false)
		{
			int rand1 = rand() % 10;
			if (rand1 == 1)
			{
				bricks[0][j].exists(true);
				bricks[0][j].setBomb(true);
				bricks[0][j].setResistance(1);
			}
		}
	}

}

void Game :: destroyBricks(int i , int j)
{

	for (int k = -1 ; k <= 1 ; k++)
	{
		for (int m = -1; m <= 1; m++)
		{

			if (i + k != -1 && i + k != BRICK_ROWS - 1 && j + m != BRICK_COLUMNS - 1 && j + m != -1)
			{
				bricks[i + k][j + m].exists(false);
				bricks[i + k][j + m].setBomb(false);
			}
		}
	}
}
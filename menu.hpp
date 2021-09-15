#include <cstdlib>
#include <vector>
#include <algorithm>

#include "button.hpp"
#include "game.hpp"

#define FONT_FREESANS "FreeSans.ttf"
#define ENTER 13
#define UP 82
#define DOWN 81
#define RIGHT 79
#define LEFT 80
#define NEWGAME 0
#define SCOREBOARD 1
#define EDITUSERNAME 2
#define EXIT 3
#define BUTTON_X 50
#define BUTTON1_Y 50
#define BUTTON2_Y 175
#define BUTTON3_Y 300
#define BUTTON4_Y 425
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 100
#define BUTTONS_COLOUR RED
#define FONT_SIZE 18
#define BUTTON1_LABLE "New Game"
#define BUTTON2_LABLE "Scoreboard"
#define BUTTON3_LABLE "Edit Username"
#define BUTTON4_LABLE "Exit"
#define NUMER_OF_BUTTONS 4
#define BACKGROUND "star.jpg"
#define BACKSPACE 8
#define GAME_NAME "‫‪Swipe‬‬ ‫‪Brick‬‬ ‫‪Breakers‬‬"
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 575

#define RECORD_X 140
#define RECORD_Y 250
#define SCORE_X 225
#define SCORE_Y 200
#define SCORE_LABLE_X 140
#define SCORE_LABLE_Y 200
#define GAME_OVER_LABLE_X 140
#define GAME_OVER_LABLE_Y 60
#define GAME_OVER_LABLE_FONT 40
#define GAMEOVER_RECT1_X 100
#define GAMEOVER_RECT1_Y 50
#define GAMEOVER_RECT1_WIDTH 300
#define GAMEOVER_RECT1_HEIGHT 80
#define GAMEOVER_RECT2_X 125
#define GAMEOVER_RECT2_Y 170
#define GAMEOVER_RECT2_WIDTH 250
#define GAMEOVER_RECT2_HEIGHT 200
#define GAMEOVER_RECT1_SELECT_X 90
#define GAMEOVER_RECT1_SELECT_Y 40
#define GAMEOVER_RECT1_SELECT_WIDTH 320
#define GAMEOVER_RECT1_SELECT_HEIGHT 100

#define ENTER_USERNAME_X 90
#define ENTER_USERNAME_Y 50
#define ENTER_USERNAME_FONT 24
#define EDITUSERNAME_RECT1_X 50
#define EDITUSERNAME_RECT1_Y 100
#define EDITUSERNAME_RECT1_WIDTH 400
#define EDITUSERNAME_RECT1_HEIGHT 100
#define USERNAME_X 75
#define USERNAME_Y 125
#define CANCLE_BUTTON_X 40
#define CANCLE_BUTTON_Y 425
#define SAVE_BUTTON_X 260
#define SAVE_BUTTON_Y 425

#define RECORDS_X 150
#define RECORDS_Y 50
#define RECORDS_FONT 24
#define SCOREBOARD_RECT1_X 50
#define SCOREBOARD_RECT1_Y 100
#define SCOREBOARD_RECT1_WIDTH 400
#define SCOREBOARD_RECT1_HEIGHT 325
#define MENU_BUTTON_X 150
#define MENU_BUTTON_Y 450
#define USERNAMES_X 60
#define USERNAMES_Y 115
#define USERSCORE_X 400
#define USERSCORE_Y 115



class Menu {
private:
	Window* win;
	User activeUser;
	std::vector<User> users;
	Button button[NUMER_OF_BUTTONS] , menuButton , saveButton, cancleButton;
	int buttonName;
	Event lastEvent;
	Game game;
	bool exit , userExist;
public:
	void load();
	void openWindow();
	void draw();
	void drawButtons();
	void doProcess();
	void handleLastEvent();
	void chooseButton(int);
	void openPage();
	void showScoreBoard();
	void editUserName();
	std::string eraseLastChar(std::string);
	int searchUser(std::string);
	void gameOver();
	void drawScoreBoard();
};
#include "menu.hpp"

#define GAME_NAME "‫‪Swipe‬‬ ‫‪Brick‬‬ ‫‪Breakers‬‬"
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 575

class TotalSystem{
private:
	Window* window;
	Menu menu;
public:
	void openWindow();
	//TotalSystem(){menu = Menu();}
	void showMenu();
};


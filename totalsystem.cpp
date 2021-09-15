#include "totalsystem.hpp"

void TotalSystem :: showMenu()
{
	menu.setWindow(window);
	menu.doProcess();
} 

void TotalSystem :: openWindow()
{
	window =new Window(WINDOW_WIDTH,WINDOW_HEIGHT, GAME_NAME);
}
#include "menu.hpp"

using namespace std;
void Menu :: openWindow()
{
    win = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_NAME);
    button[NEWGAME] = Button(BUTTON_X, BUTTON1_Y, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTONS_COLOUR, 102, 90, BUTTON1_LABLE, FONT_FREESANS, FONT_SIZE);
    button[SCOREBOARD] = Button(BUTTON_X, BUTTON2_Y, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTONS_COLOUR, 95, 215, BUTTON2_LABLE, FONT_FREESANS, FONT_SIZE);
    button[EDITUSERNAME] = Button(BUTTON_X, BUTTON3_Y, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTONS_COLOUR, 90, 340, BUTTON3_LABLE, FONT_FREESANS, FONT_SIZE);
    button[EXIT] = Button(BUTTON_X, BUTTON4_Y, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTONS_COLOUR, 130, 465, BUTTON4_LABLE, FONT_FREESANS, FONT_SIZE);

    button[NEWGAME].setWindow(win);
    button[SCOREBOARD].setWindow(win);
    button[EDITUSERNAME].setWindow(win);
    button[EXIT].setWindow(win);

    exit = 0;
    userExist = 0;
}

void Menu :: load()
{
    openWindow();
    doProcess();
}

void Menu :: draw()
{
    win->clear();
    win->draw_bg(BACKGROUND, 0, 0);
    drawButtons();
    win->update_screen();
}

void Menu::drawButtons()
{
    button[NEWGAME].draw();
    button[SCOREBOARD].draw();
    button[EDITUSERNAME].draw();
    button[EXIT].draw();
    button[buttonName].choose();
}

void Menu :: doProcess()
{
    buttonName = NEWGAME;

    while (!exit)
    {
        draw();
        handleLastEvent();

    }
}

void Menu::handleLastEvent()
{
    lastEvent = win->pollForEvent();
    if (lastEvent.type() == KEY_PRESS)
    {
        if (lastEvent.pressedKey() == ENTER)
        {
            openPage();
            if (buttonName == EXIT)
                exit = 1;
        }
        if (lastEvent.pressedKey() == UP)
        {
            if (buttonName == NEWGAME)
                buttonName = EXIT;
            else
                buttonName = buttonName - 1;
        }
        if (lastEvent.pressedKey() == DOWN)
        {
            if (buttonName == EXIT)
                buttonName = NEWGAME;
            else
                buttonName = buttonName + 1;
        }
    }
}

void Menu :: openPage()
{
    if (buttonName == EXIT)
    {
        return;
    }

    if (buttonName == NEWGAME)
    {
        game.setWindow(win);
        game.load();
        game.setPlayer(activeUser);
        gameOver();
        userExist  = true;
    }

    if (buttonName == EDITUSERNAME)
    {
        editUserName();
    }

    if (buttonName == SCOREBOARD)
    {
        showScoreBoard();
    }
}

void Menu :: showScoreBoard()
{
    while (true)
    {
        lastEvent = win->pollForEvent();
        if (lastEvent.type() == KEY_PRESS)
        {
            if (lastEvent.pressedKey() == ENTER)
            {
                break;
            }
        }
        drawScoreBoard();

    }
}

void Menu:: drawScoreBoard()
{
    win->clear();
    win->draw_bg(BACKGROUND, 0, 0);
    win->show_text("Records :" , RECORDS_X , RECORDS_Y, BLACK, FONT_FREESANS, RECORDS_FONT);
    win->fill_rect(SCOREBOARD_RECT1_X, SCOREBOARD_RECT1_Y, SCOREBOARD_RECT1_WIDTH, SCOREBOARD_RECT1_HEIGHT, WHITE);
    win->draw_rect(SCOREBOARD_RECT1_X, SCOREBOARD_RECT1_Y, SCOREBOARD_RECT1_WIDTH, SCOREBOARD_RECT1_HEIGHT, BLACK);
    menuButton = Button(MENU_BUTTON_X, MENU_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTONS_COLOUR, 228, 492, "Menu", FONT_FREESANS, FONT_SIZE);
    menuButton.setWindow(win);
    menuButton.draw();
    menuButton.choose();
    std::sort(users.begin(), users.end());
    for (int i = 0; i < users.size(); i++)
    {
        win->show_text(users[i].getName(), USERNAMES_X, USERNAMES_Y + 59 * i, BLACK, FONT_FREESANS, FONT_SIZE);
        win->show_text(std::to_string(users[i].getBestScore()), USERSCORE_X, USERSCORE_Y + 59 * i, BLACK, FONT_FREESANS, FONT_SIZE);
    }
    win->update_screen();
}


void Menu :: editUserName()
{
    std::string userName = activeUser.getName();
    int buttonNameumber = 0 ;
    while (true)
    {
        lastEvent = win->pollForEvent();
        if (lastEvent.type() == KEY_PRESS)
        {
            if (lastEvent.pressedKey() == ENTER )
            {
                if (buttonNameumber == 0)
                {
                    if (searchUser(userName) == -1)
                    {
                        User newUser(userName, 0);
                        users.push_back(newUser);
                        activeUser = newUser;
                        userExist = true;
                    }
                }
                break;
            }
            else if (lastEvent.pressedKey() == RIGHT || lastEvent.pressedKey() == LEFT)
            {
                if (buttonNameumber == 0)
                    buttonNameumber = 1;
                else if (buttonNameumber == 1)
                    buttonNameumber = 0;
            }
            else
            {
                if (lastEvent.pressedKey() == BACKSPACE)
                    userName = eraseLastChar(userName);
                else
                {
                    userName += lastEvent.pressedKey();
                }
            }
        }
        win->clear();
        win->draw_bg(BACKGROUND, 0, 0);
        win->show_text("Enter Username :" , ENTER_USERNAME_X , ENTER_USERNAME_Y, BLACK, FONT_FREESANS, ENTER_USERNAME_FONT);
        win->fill_rect(EDITUSERNAME_RECT1_X, EDITUSERNAME_RECT1_Y, EDITUSERNAME_RECT1_WIDTH, EDITUSERNAME_RECT1_HEIGHT, WHITE);
        win->draw_rect(EDITUSERNAME_RECT1_X, EDITUSERNAME_RECT1_Y, EDITUSERNAME_RECT1_WIDTH, EDITUSERNAME_RECT1_HEIGHT, BLACK);
        if (userName.size())
            win->show_text(userName, USERNAME_X, USERNAME_Y, BLACK, FONT_FREESANS, FONT_SIZE);
        cancleButton = Button(CANCLE_BUTTON_X, CANCLE_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTONS_COLOUR, 118, 465, "cancle", FONT_FREESANS, FONT_SIZE);
        cancleButton.setWindow(win);
        cancleButton.draw();
        saveButton = Button(SAVE_BUTTON_X, SAVE_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTONS_COLOUR, 340, 465, "save", FONT_FREESANS, FONT_SIZE);
        saveButton.setWindow(win);
        saveButton.draw();
        if (buttonNameumber == 0)
            saveButton.choose();
        if (buttonNameumber == 1)
            cancleButton.choose();
        win->update_screen();
    }

}

std::string Menu::eraseLastChar(std::string inputString)
{
    if (inputString.size() > 0)
        inputString.erase(inputString.size() - 1);
    return inputString;
}

int Menu :: searchUser(std::string userName)
{
    for (int i = 0 ; i < users.size() ; i++)
    {
        if (users[i].getName() == userName)
        {
            return i;
        }
    }
    return -1;
}

void Menu :: gameOver()
{
    Button newGame, toMenu;
    int buttonNumber = 0;
    newGame = Button(260, 425, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTONS_COLOUR, 318, 465, "New Game", FONT_FREESANS, FONT_SIZE);
    toMenu = Button(40, 425, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTONS_COLOUR, 118, 465, "Menu", FONT_FREESANS, FONT_SIZE);
    newGame.setWindow(win);
    toMenu.setWindow(win);
    while (true)
    {
        lastEvent = win->pollForEvent();
        if (lastEvent.type() == KEY_PRESS)
        {
            if (lastEvent.pressedKey() == ENTER )
            {
                if (buttonNumber == 1)
                {
                    break;
                }
                if (buttonNumber == 0)
                {
                    buttonName = NEWGAME;
                    openPage();
                }
            }
            else if (lastEvent.pressedKey() == RIGHT || lastEvent.pressedKey() == LEFT)
            {
                if (buttonNumber == 0)
                    buttonNumber = 1;
                else if (buttonNumber == 1)
                    buttonNumber = 0;
            }
        }
        win->clear();
        win->draw_bg(BACKGROUND, 0, 0);
        win->fill_rect(GAMEOVER_RECT1_X, GAMEOVER_RECT1_Y, GAMEOVER_RECT1_WIDTH, GAMEOVER_RECT1_HEIGHT, RED);
        win->draw_rect(GAMEOVER_RECT1_X, GAMEOVER_RECT1_Y, GAMEOVER_RECT1_WIDTH, GAMEOVER_RECT1_HEIGHT, BLACK);
        win->draw_rect(GAMEOVER_RECT1_SELECT_X, GAMEOVER_RECT1_SELECT_Y, GAMEOVER_RECT1_SELECT_WIDTH, GAMEOVER_RECT1_SELECT_HEIGHT, BLACK);
        win->show_text("Game Over" , GAME_OVER_LABLE_X , GAME_OVER_LABLE_Y, BLACK, FONT_FREESANS, GAME_OVER_LABLE_FONT);
        win->fill_rect(GAMEOVER_RECT2_X, GAMEOVER_RECT2_Y, GAMEOVER_RECT2_WIDTH, GAMEOVER_RECT2_HEIGHT, WHITE);
        win->draw_rect(GAMEOVER_RECT2_X, GAMEOVER_RECT2_Y, GAMEOVER_RECT2_WIDTH, GAMEOVER_RECT2_HEIGHT, BLACK);
        win->show_text("Score :", SCORE_LABLE_X, SCORE_LABLE_Y, BLACK, FONT_FREESANS, FONT_SIZE);
        win->show_text(to_string(game.getScore()), SCORE_X, SCORE_Y, BLACK, FONT_FREESANS, FONT_SIZE);
        win->show_text("Record :", RECORD_X, RECORD_Y, BLACK, FONT_FREESANS, FONT_SIZE);


        toMenu.draw();
        newGame.draw();
        if (buttonNumber == 0)
        {
            newGame.choose();
        }
        if (buttonNumber == 1)
        {
            toMenu.choose();
        }
        win->update_screen();

    }
}
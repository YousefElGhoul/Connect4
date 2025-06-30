#include "../include/Navigation.hpp"

char arrow;
int counter = 0;

void GameNavigation::MoveLeft(){
    selector -= 1;
    selector = selector <= 0 ? selector + BOARD_WIDTH : selector;
    if (board_selector[selector - 1] == 'F')
        MoveLeft();
    else{
        GameNavigation::removeSelector();
        board_selector[selector - 1] = '^';
    }
}
void GameNavigation::MoveRight(){
    selector += 1;
    selector = selector > BOARD_WIDTH ? selector - BOARD_WIDTH : selector;
    if (board_selector[selector - 1] == 'F')
        MoveRight();
    else{
        GameNavigation::removeSelector();
        board_selector[selector - 1] = '^';
    }
}
void GameNavigation::checkFullColumns(){
    for (int i = 0; i < BOARD_WIDTH; i++)
        if(board[i] != 0)
            board_selector[i] = 'F';
}
void GameNavigation::removeSelector() {
    for (int i = 0; i < BOARD_WIDTH; i++)
        if (board_selector[i] == '^')
            board_selector[i] = ' ';
}

void GameNavigation::Nav() {
    arrow = getch();
    do {
        switch (arrow) {
        case KEY_ESC:
            exitProgram();
        default:
            arrow = getch();
            switch (arrow) {
            case KEY_LEFT:
                GameNavigation::MoveLeft();
                Display::showBoard();
                break;
            case KEY_RIGHT:
                GameNavigation::MoveRight();
                Display::showBoard();
                break;
            case KEY_ESC:
                exitProgram();
            default:
                break;
            }
            break;
        }
    } while (arrow != KEY_ENTER);
}

void MenuNavigation::Nav(int button1, int button2) {
    arrow = getch();
    do {
        switch (arrow) {
        case KEY_ESC:
            exitProgram();
        default:
            arrow = getch();
            switch (arrow) {
            case KEY_UP:
                Display::showMenu(button1);
                selector = '1';
                break;
            case KEY_DOWN:
                Display::showMenu(button2);
                selector = '2';
                break;
            case KEY_ESC:
                exitProgram();
            default:
                break;
            }
            break;
        }
    } while (arrow != KEY_ENTER);
}
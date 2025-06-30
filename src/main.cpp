#include <iostream>
#include "../include/Scores.hpp"
#include "../include/Display.hpp"
#include "../include/Connect4.hpp"
#include "../include/Menus.hpp"

void initProgram(){
    Scores::checkFile();
    Scores::readHighScores();
    Display::init();
    Connect4::initGame();
    Menus::select(START);
}

int main(){
    initProgram();
    Display::shellCommand(PAUSE);
    exitProgram();
}
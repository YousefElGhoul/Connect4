#ifndef CONNECT4_HPP
#define CONNECT4_HPP

#include <unistd.h>
#include "utils.hpp"
#include "Display.hpp"

#define GAME_STATE_DRAW             0
#define GAME_STATE_RESULT           1
#define GAME_STATE_ONGOING          -1

#define WIN_PATTERN_COUNT           4

class Connect4 {
public:
    static void initGame();
    static int checkWin();
    static void gravitySim(int *dropChoice);

private:
    static void clearBoard();
};

#endif
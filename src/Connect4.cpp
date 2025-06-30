#include "../include/Connect4.hpp"

void Connect4::initGame(){
    clearBoard();
}

void Connect4::gravitySim(int *dropChoice){
    sleep(1);
    if(*(dropChoice + BOARD_WIDTH) == 0){
        *(dropChoice + BOARD_WIDTH) = *dropChoice;
        *dropChoice = 0;
        Display::showBoard();
        gravitySim(dropChoice + BOARD_WIDTH);
    }else return;
}

int Connect4::checkWin() {
    int winPatterns[WIN_PATTERN_COUNT][4] = {
        {0, 1, 2, 3},                                                   // Horizontal
        {0, BOARD_WIDTH, BOARD_WIDTH*2, BOARD_WIDTH*3},                 // Vertical
        {0, BOARD_WIDTH + 1, (BOARD_WIDTH + 1)*2, (BOARD_WIDTH + 1)*3}, // \ Diagonal
        {0, BOARD_WIDTH - 1, (BOARD_WIDTH - 1)*2, (BOARD_WIDTH - 1)*3}  // / Diagonal
    };
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int p = 0; p < WIN_PATTERN_COUNT; ++p) {
            int a = i + winPatterns[p][0];
            int b = i + winPatterns[p][1];
            int c = i + winPatterns[p][2];
            int d = i + winPatterns[p][3];

            // Bounds check
            if (a >= BOARD_SIZE || b >= BOARD_SIZE || c >= BOARD_SIZE || d >= BOARD_SIZE)
                continue;

            // Prevent horizontal wraparound
            if (p == 0 && (i % BOARD_WIDTH) > BOARD_WIDTH - 4)
                continue;

            // Prevent diagonal / wraparound
            if (p == 3 && (i % BOARD_WIDTH) < 3)
                continue;

            if (board[a] != 0 &&
                board[a] == board[b] &&
                board[b] == board[c] &&
                board[c] == board[d]) {
                return GAME_STATE_RESULT;
            }
        }
    }
    
    // Draw check
    bool full = true;
    for (int i = 0; i < BOARD_SIZE; ++i)
        if (board[i] == 0) {
            full = false;
            break;
        }

    if (full)
        return GAME_STATE_DRAW;

    return GAME_STATE_ONGOING;
}

void Connect4::clearBoard() {
    for (int i = 0; i < BOARD_SIZE; i++)
        board[i] = ' ';
}
#include "../include/Connect4.hpp"

void Connect4::initGame(){
    clearBoard();
}

void Connect4::gravitySim(int *dropChoice){
    // Base case: if we're already at the bottom row, or next cell is taken
    if ((dropChoice + BOARD_WIDTH) >= board + (BOARD_WIDTH * BOARD_HEIGHT) || *(dropChoice + BOARD_WIDTH) != 0) {
        return;
    }
    
    // Move the piece down
    *(dropChoice + BOARD_WIDTH) = *dropChoice;
    *dropChoice = 0;

    // Update the display
    Display::showBoard();
    usleep(250000); // Sleep for 250 milliseconds to simulate gravity

    // Continue simulation further down
    gravitySim(dropChoice + BOARD_WIDTH);
}

int Connect4::checkWin() {
    int winPatterns[WIN_PATTERN_COUNT][4] = {
        {0, 1, 2, 3},                                                   // Horizontal
        {0, BOARD_WIDTH, BOARD_WIDTH*2, BOARD_WIDTH*3},                 // Vertical
        {0, BOARD_WIDTH + 1, (BOARD_WIDTH + 1)*2, (BOARD_WIDTH + 1)*3}, // \ Diagonal
        {0, BOARD_WIDTH - 1, (BOARD_WIDTH - 1)*2, (BOARD_WIDTH - 1)*3}  // / Diagonal
    };
    for (int i = 0; i < BOARD_SIZE; ++i) {
        int row = i / BOARD_WIDTH;
        int col = i % BOARD_WIDTH;

        for (int p = 0; p < WIN_PATTERN_COUNT; ++p) {
            int a = i + winPatterns[p][0];
            int b = i + winPatterns[p][1];
            int c = i + winPatterns[p][2];
            int d = i + winPatterns[p][3];

            // Bounds check
            if (a >= BOARD_SIZE || b >= BOARD_SIZE || c >= BOARD_SIZE || d >= BOARD_SIZE)
                continue;

            // Horizontal wrap check
            if (p == 0 && col > BOARD_WIDTH - 4) continue;

            // \ Diagonal: moves right and down
            if (p == 2 && (col > BOARD_WIDTH - 4 || row > BOARD_HEIGHT - 4)) continue;

            // / Diagonal: moves left and down
            if (p == 3 && (col < 3 || row > BOARD_HEIGHT - 4)) continue;

            // Vertical: just ensure room below
            if (p == 1 && row > BOARD_HEIGHT - 4) continue;

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
        board[i] = 0;
}
#ifndef UTILS_HPP
#define UTILS_HPP

#define BOARD_HEIGHT 6
#define BOARD_WIDTH 7
#define BOARD_SIZE 42

#include "PlayerData.hpp"

extern int board[BOARD_SIZE];
extern char board_selector[BOARD_WIDTH];
extern int selector, player;
extern std::string lineInput;

extern PlayerData *player1;
extern PlayerData *player2;

int isEven(int x);
std::string getCurrentPlayersName(int player);

#endif
#ifndef UTILS_HPP
#define UTILS_HPP

#include "PlayerData.hpp"

#define BOARD_HEIGHT 6
#define BOARD_WIDTH 7
#define BOARD_SIZE 42

extern int board[BOARD_SIZE];
extern char board_selector[BOARD_WIDTH];
extern int selector, player;

extern PlayerData *player1;
extern PlayerData *player2;

int isEven(int x);
std::string getCurrentPlayersName(int player);

#endif
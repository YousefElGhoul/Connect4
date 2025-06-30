#include "../include/utils.hpp"

int board[BOARD_SIZE] = {};
char board_selector[BOARD_WIDTH] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
int selector, player = 1;
std::string lineInput;

PlayerData *player1 = new PlayerData("", 0);
PlayerData *player2 = new PlayerData("", 0);

int isEven(int x) { return x % 2 == 0 ? 2 : 1; }
std::string getCurrentPlayersName(int player) { return isEven(player) == 1 ? player1->getName() : player2->getName(); }
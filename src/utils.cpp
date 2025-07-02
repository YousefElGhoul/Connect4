#include "../include/utils.hpp"

int board[BOARD_SIZE] = { 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0 };
char board_selector[BOARD_WIDTH] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
int selector = 1, player = 1;

PlayerData *player1 = new PlayerData("", 0);
PlayerData *player2 = new PlayerData("", 0);

int isEven(int x) { return x % 2 == 0 ? 2 : 1; }
std::string getCurrentPlayersName(int player) { return isEven(player) == 1 ? player1->getName() : player2->getName(); }
bool allMatch(const char* arr, size_t length, char target) {
    for (size_t i = 0; i < length; ++i) {
        if (arr[i] != target) return false;
    }
    return true;
}
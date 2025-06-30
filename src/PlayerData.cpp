#include "PlayerData.hpp"

PlayerData::PlayerData(std::string str, int num) : name(str), score(num) {}

void PlayerData::setName(std::string str) { name = str; }
void PlayerData::setScore(int num) { score = num; }

std::string PlayerData::getName() { return name; }
int PlayerData::getScore() { return score; }

bool PlayerData::isEmpty() { return name.empty(); }
void PlayerData::incScore() { score++; }

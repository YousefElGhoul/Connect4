#ifndef SCORES_HPP
#define SCORES_HPP

#include <fstream>
#include "PlayerData.hpp"
#include "utils.hpp"

#define HIGH_SCORE_FILE_ARRAY_SIZE  5
#define HIGH_SCORE_FILE_NAME        "high_scores.dat"
#define HIGH_SCORE_FILE_DEFAULT     "Yousef\nNicole\nOwen\nPenny\nMalika\n10\n9\n8\n7\n6\n"

extern PlayerData *empty;
extern PlayerData High_Scores[HIGH_SCORE_FILE_ARRAY_SIZE];

class Scores {
public:
    static void checkFile();
    static void readHighScores();
    static void saveHighScores();
    static void refreshHighScores();

private:
    static void swapData(PlayerData* xp, PlayerData* yp);
    static void sortData();
    static void addScore(PlayerData pd);
};

#endif
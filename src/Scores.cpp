#include "../include/Scores.hpp"

PlayerData *empty = new PlayerData("", 0);
PlayerData High_Scores[HIGH_SCORE_FILE_ARRAY_SIZE] = {*empty, *empty, *empty, *empty, *empty};

void Scores::checkFile(){
    std::fstream file;
    file.open(HIGH_SCORE_FILE_NAME);
    if(!file){
        file.open(HIGH_SCORE_FILE_NAME, std::ios::out);
        if(file.is_open()){
            file << HIGH_SCORE_FILE_DEFAULT;
            file.close();
        }
    }
    file.close();
}
void Scores::readHighScores(){
    std::fstream file;
    file.open(HIGH_SCORE_FILE_NAME, std::ios::in);
    if(file.is_open()){
        for (int i = 0; i < HIGH_SCORE_FILE_ARRAY_SIZE; i++){
            getline(file, lineInput);
            High_Scores[i].setName(lineInput);
        }
        for (int i = 0; i < HIGH_SCORE_FILE_ARRAY_SIZE; i++){
            getline(file, lineInput);
            High_Scores[i].setScore(stoi(lineInput));
        }
        file.close();
        sortData();
    }
}
void Scores::saveHighScores(){
    std::fstream file;
    file.open(HIGH_SCORE_FILE_NAME, std::ios::out);
    if(file.is_open()){
        for (int i = 0; i < HIGH_SCORE_FILE_ARRAY_SIZE; i++)
            file << High_Scores[i].getName() << "\n";
        for (int i = 0; i < HIGH_SCORE_FILE_ARRAY_SIZE; i++)
            file << High_Scores[i].getScore() << "\n";
        file.close();
    }
}
void Scores::refreshHighScores(){
    addScore(*player1);
    addScore(*player2);
    saveHighScores();
}
void Scores::swapData(PlayerData* xp, PlayerData* yp){
    PlayerData temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void Scores::sortData(){
    for (int i = 0; i < HIGH_SCORE_FILE_ARRAY_SIZE - 1; i++)
        for (int j = 0; j < HIGH_SCORE_FILE_ARRAY_SIZE - i - 1; j++)
            if(High_Scores[j].getScore() < High_Scores[j+1].getScore())
                swapData(&High_Scores[j], &High_Scores[j+1]);
}
void Scores::addScore(PlayerData pd){
    if(pd.getScore() > High_Scores[HIGH_SCORE_FILE_ARRAY_SIZE - 1].getScore()){
        High_Scores[HIGH_SCORE_FILE_ARRAY_SIZE - 1] = pd;
        sortData();
    }
}
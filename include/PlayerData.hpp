#ifndef PLAYERDATA_HPP
#define PLAYERDATA_HPP

#include <string>

class PlayerData {
public:
    PlayerData(std::string str = "", int num = 0);

    void setName(std::string str);
    void setScore(int num);

    std::string getName();
    int getScore();

    bool isEmpty();
    void incScore();
private:
    std::string name;
    int score;
};

#endif
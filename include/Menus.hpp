#ifndef MENUS_HPP
#define MENUS_HPP

#include <cstdlib>
#include "Display.hpp"
#include "Navigation.hpp"
#include "Connect4.hpp"
#include "Scores.hpp"

#define START                       0
#define NAME                        1
#define GAME                        2
#define WIN                         3
#define DRAW                        4
#define HIGH_SCORES                 5
#define RESTART                     6

class Menus {
public:
    static void select(int menu);
};

[[noreturn]] void exitProgram();

#endif
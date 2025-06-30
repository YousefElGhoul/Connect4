#ifndef NAVIGATION_HPP
#define NAVIGATION_HPP

#include <conio.h>
#include "Display.hpp"
#include "Menus.hpp"

#define KEY_UP                      72
#define KEY_DOWN                    80
#define KEY_LEFT                    75
#define KEY_RIGHT                   77
#define KEY_ENTER                   13
#define KEY_ESC                     27

class MenuNavigation {
public:
    static void Nav(int button1, int button2);
};

class GameNavigation {
public:
    static void MoveLeft();
    static void MoveRight();
    static void checkFullColumns();
    static void Nav();
private:
    static void removeSelector();
};

#endif
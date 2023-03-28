#include <iostream>
#include <unistd.h>
#include <conio.h>

#define LOGO "\t\t\t ██████╗ ███████╗ ███╗   ██╗███╗   ██╗███████╗ ██████╗████████╗    ██╗  ██╗\n\t\t\t██╔════╝██╔════██╗████╗  ██║████╗  ██║██╔════╝██╔════╝╚══██╔══╝    ██║  ██║\n\t\t\t██║     ██║    ██║██╔██╗ ██║██╔██╗ ██║█████╗  ██║        ██║       ███████║\n\t\t\t██║     ██║    ██║██║╚██╗██║██║╚██╗██║██╔══╝  ██║        ██║       ╚════██║\n\t\t\t╚██████╗╚███████╔╝██║ ╚████║██║ ╚████║███████╗╚██████╗   ██║            ██║\n\t\t\t ╚═════╝ ╚══════╝ ╚═╝  ╚═══╝╚═╝  ╚═══╝╚══════╝ ╚═════╝   ╚═╝            ╚═╝\n"

#define START 0
#define START_MENU "\t\t\t ██████╗ ███████╗ ███╗   ██╗███╗   ██╗███████╗ ██████╗████████╗    ██╗  ██╗\n\t\t\t██╔════╝██╔════██╗████╗  ██║████╗  ██║██╔════╝██╔════╝╚══██╔══╝    ██║  ██║\n\t\t\t██║     ██║    ██║██╔██╗ ██║██╔██╗ ██║█████╗  ██║        ██║       ███████║\n\t\t\t██║     ██║    ██║██║╚██╗██║██║╚██╗██║██╔══╝  ██║        ██║       ╚════██║\n\t\t\t╚██████╗╚███████╔╝██║ ╚████║██║ ╚████║███████╗╚██████╗   ██║            ██║\n\t\t\t ╚═════╝ ╚══════╝ ╚═╝  ╚═══╝╚═╝  ╚═══╝╚══════╝ ╚═════╝   ╚═╝            ╚═╝\n   ________________________\n  |                        |\n  |         START          |\n  |________________________|\n   ________________________\n  |                        |\n  |         EXIT           |\n  |________________________|\n"
#define START_MENU_START_SELECTED "\t\t\t ██████╗ ███████╗ ███╗   ██╗███╗   ██╗███████╗ ██████╗████████╗    ██╗  ██╗\n\t\t\t██╔════╝██╔════██╗████╗  ██║████╗  ██║██╔════╝██╔════╝╚══██╔══╝    ██║  ██║\n\t\t\t██║     ██║    ██║██╔██╗ ██║██╔██╗ ██║█████╗  ██║        ██║       ███████║\n\t\t\t██║     ██║    ██║██║╚██╗██║██║╚██╗██║██╔══╝  ██║        ██║       ╚════██║\n\t\t\t╚██████╗╚███████╔╝██║ ╚████║██║ ╚████║███████╗╚██████╗   ██║            ██║\n\t\t\t ╚═════╝ ╚══════╝ ╚═╝  ╚═══╝╚═╝  ╚═══╝╚══════╝ ╚═════╝   ╚═╝            ╚═╝\n\t   ________________________\n\t  |                        |\n\t  |         START          |\n\t  |________________________|\n   ________________________\n  |                        |\n  |         EXIT           |\n  |________________________|\n"
#define START_MENU_EXIT_SELECTED "\t\t\t ██████╗ ███████╗ ███╗   ██╗███╗   ██╗███████╗ ██████╗████████╗    ██╗  ██╗\n\t\t\t██╔════╝██╔════██╗████╗  ██║████╗  ██║██╔════╝██╔════╝╚══██╔══╝    ██║  ██║\n\t\t\t██║     ██║    ██║██╔██╗ ██║██╔██╗ ██║█████╗  ██║        ██║       ███████║\n\t\t\t██║     ██║    ██║██║╚██╗██║██║╚██╗██║██╔══╝  ██║        ██║       ╚════██║\n\t\t\t╚██████╗╚███████╔╝██║ ╚████║██║ ╚████║███████╗╚██████╗   ██║            ██║\n\t\t\t ╚═════╝ ╚══════╝ ╚═╝  ╚═══╝╚═╝  ╚═══╝╚══════╝ ╚═════╝   ╚═╝            ╚═╝\n   ________________________\n  |                        |\n  |         START          |\n  |________________________|\n\t   ________________________\n\t  |                        |\n\t  |         EXIT           |\n\t  |________________________|\n"
#define GAME 1
#define WIN 2
#define DRAW 3
#define NAME 4
#define HIGH_SCORES 5
#define RESTART 6

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27

int board[49] = {};
char arrow;
int selector, player = 1;
std::string lineInput;
class PlayerData{
    public:
        PlayerData(std::string str, int num): name(str), score(num){};


        void setName(std::string str){name = str;}
        void setScore(int num){score = num;}
        std::string getName(){return name;}
        int getScore(){return score;}

        bool isEmpty(){return name.empty();}
        void incScore(){score++;}
    private:
        std::string name;
        int score;
};

PlayerData *player1 = new PlayerData("", 0);
PlayerData *player2 = new PlayerData("", 0);
const PlayerData *empty = new PlayerData("", 0);

int isEven(int x){return x % 2 == 0 ? 2 : 1;}
std::string getName(int player){return isEven(player) == 1 ? player1->getName() : player2->getName();}


class Display{
    public:
        static void initDisplay(){
            system("chcp 65001");
            system("color a");
            clear();
        }
        static void refresh(std::string str){
            clear();
            print(str);
        }
    private:
        static void clear(){system("CLS");}
        static void print(std::string str){std::cout << "\u001b[36m" << str;}
};

class Connect4{
    public:
        static void initGame(){
            clearBoard();
        }
        static int checkWin(){
            // To be Implemented
        }
    private:
        static void clearBoard() {
            for (int i = 0; i < 42; i++)
                board[i] = 0;
        }
};

void exitProgram(){exit(0);}

class Menus{
    public:
        static void select(int menu){
            switch (menu){
            case START:
                Display::refresh(START_MENU);
                arrow = getch();
                do{
                    switch (arrow){
                    case KEY_ESC:
                        exitProgram();
                    default:
                        arrow = getch();
                        switch (arrow){
                        case KEY_UP:
                            Display::refresh(START_MENU_START_SELECTED);
                            selector = 'S';
                            break;
                        case KEY_DOWN:
                            Display::refresh(START_MENU_EXIT_SELECTED);
                            selector = 'E';
                            break;
                        case KEY_ESC:
                            exitProgram();
                        default:
                            break;
                        }
                        break;
                    }
                }while (arrow != KEY_ENTER);
                switch (selector){
                case 'S':
                    Menus::select(NAME);
                    break;
                case 'E':
                    exitProgram();
                default:
                    break;
                }
                break;
            case NAME:
                Display::refresh(LOGO);
                std::cout << "Player 1: \n";
                getline(std::cin, lineInput);
                player1->setName(lineInput);
                if(player1->isEmpty())
                    player1->setName("Player 1");
                std::cout << "\nPlayer 2: \n";
                getline(std::cin, lineInput);
                player2->setName(lineInput);
                if(player2->isEmpty())
                    player2->setName("Player 2");
                Menus::select(GAME);
                break;
            default:
                std::cout << "\nMissing Screen!\n";
                sleep(1);
                break;
            }
        }
};

void initProgram(){
    Display::initDisplay();
    Connect4::initGame();
    Menus::select(START);
}

int main(){
    initProgram();
    sleep(3);
    return 0;
}
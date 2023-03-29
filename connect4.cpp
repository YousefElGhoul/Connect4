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

#define GAME_STATE_DRAW 0
#define GAME_STATE_RESULT 1
#define GAME_STATE_ONGOING -1

#define BOARD_HEIGHT 6
#define BOARD_WIDTH 7

int board[BOARD_HEIGHT][BOARD_WIDTH] = {};
char board_selector[BOARD_WIDTH] = {};
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
            system("mode con: cols=121 lines=40");
            clear();
        }
        static void refresh(std::string str){
            clear();
            print(str);
        }
        static void printBoard(){
            std::cout << std::endl << player1->getName() << " (\u001b[31mO\u001b[36m) Score [" << player1->getScore() << "]  -  " << player2->getName() << " (\u001b[33mO\u001b[36m) Score [" << player2->getScore() << "]" << std::endl << std::endl
                      << "\t\t\t\t\t _________________________________________\n";
            for (int i = 0; i < BOARD_HEIGHT; i++)
                    std::cout << "\t\t\t\t\t|     |     |     |     |     |     |     |\n"
                              << "\t\t\t\t\t|  " << translateBoard(board[i][0]) << "  |  " << translateBoard(board[i][1]) << "  |  " << translateBoard(board[i][2]) << "  |  " << translateBoard(board[i][3]) << "  |  " << translateBoard(board[i][4]) << "  |  " << translateBoard(board[i][5]) << "  |  " << translateBoard(board[i][6]) << "  |\n"
                              << "\t\t\t\t\t|_____|_____|_____|_____|_____|_____|_____|\n";
            std::cout << "\n\t\t\t\t\t ";
            for (int i = 0; i < BOARD_WIDTH; i++)
                std::cout << "  " << board_selector[i] << "   ";
            std::cout << "\n\n";
        }
    private:
        static void clear(){system("CLS");}
        static void print(std::string str){std::cout << std::endl << "\u001b[36m" << str;}
        static std::string translateBoard(int n){
            switch (n){
                case 1:
                    return "\u001b[31mO\u001b[36m";
                case 2:
                    return "\u001b[33mO\u001b[36m";
                case 0:
                default:
                    return " ";
            }
        }
};

class Connect4{
    public:
        static void initGame(){
            clearBoard();
        }
        static void gravitySim(int dropChoice){
            for (int i = 0; i < BOARD_HEIGHT - 1; i++){
                if(board[i+1][dropChoice] == 0){
                    board[i+1][dropChoice] = board[i][dropChoice];
                    board[i][dropChoice] = 0;
                    Display::refresh(LOGO);
                    Display::printBoard();
                    sleep(1);
                }
                else break;
            }
        }
        static int checkWin(){
            // To be Implemented
            return -1;
        }
    private:
        static void clearBoard() {
            for (int i = 0; i < BOARD_HEIGHT; i++)
                for (int j = 0; j < BOARD_WIDTH; j++)
                    board[i][j] = 0;
        }
};

void exitProgram(){exit(0);}

class Navigation{
    public:
        static void MoveLeft(){
            selector -= 1;
            selector = selector <= 0 ? selector + BOARD_WIDTH : selector;
            if (board_selector[selector - 1] == 'F')
                MoveLeft();
            else{
                Navigation::removeSelector();
                board_selector[selector - 1] = '^';
                Display::refresh(LOGO);
                Display::printBoard();
            }
        }
        static void MoveRight(){
            selector += 1;
            selector = selector > BOARD_WIDTH ? selector - BOARD_WIDTH : selector;
            if (board_selector[selector - 1] == 'F')
                MoveRight();
            else{
                Navigation::removeSelector();
                board_selector[selector - 1] = '^';
                Display::refresh(LOGO);
                Display::printBoard();
            }
        }
        static void checkFullColumns(){
            for (int i = 0; i < BOARD_WIDTH; i++)
                if(board[0][i] != 0)
                    board_selector[i] = 'F';
        }
    private:
        static void removeSelector() {
            for (int i = 0; i < BOARD_WIDTH; i++)
                if (board_selector[i] == '^')
                    board_selector[i] = ' ';
        }
};

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
            case GAME:
                selector = 0;
                Display::refresh(LOGO);
                Display::printBoard();
                arrow = getch();
                do{
                    switch (arrow){
                    case KEY_ESC:
                        exitProgram();
                    default:
                        arrow = getch();
                        switch (arrow){
                            break;
                        case KEY_LEFT:
                            Navigation::MoveLeft();
                            break;
                        case KEY_RIGHT:
                            Navigation::MoveRight();
                            break;
                        case KEY_ESC:
                            exitProgram();
                        default:
                            break;
                        }
                        break;
                    }
                }while (arrow != KEY_ENTER);
                switch (isEven(player)){
                case 1:
                    board[0][selector - 1] = 1;
                    break;
                case 2:
                    board[0][selector - 1] = 2;
                default:
                    break;
                }
                Display::refresh(LOGO);
                Display::printBoard();
                Connect4::gravitySim(selector - 1);
                Navigation::checkFullColumns();
                switch (Connect4::checkWin()){
                case GAME_STATE_ONGOING:
                    player++;
                    Menus::select(GAME);
                    break;
                case GAME_STATE_RESULT:
                    Menus::select(WIN);
                    break;
                case GAME_STATE_DRAW:
                    Menus::select(DRAW);
                default:
                    break;
                }
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
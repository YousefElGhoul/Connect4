#include"../include/Display.hpp"

std::vector<std::string> Display::arr;

void Display::init(){
    shellCommand(UTF8);
    shellCommand(CLEAR);
    clear();
}
void Display::refresh(){
    shellCommand(CLEAR);
    for (const auto& line : arr) {
        print(line);
    }
}
void Display::showMenu(int state) {
    clear();
    switch (state) {
    case START_MENU:
        addLogo();
        addButton(START_BUTTON_TEXT);
        addButton(EXIT_BUTTON_TEXT);
        break;
    case START_MENU_START_SELECTED:
        addLogo();
        addSelectedButton(START_BUTTON_TEXT);
        addButton(EXIT_BUTTON_TEXT);
        break;
    case START_MENU_EXIT_SELECTED:
        addLogo();
        addButton(START_BUTTON_TEXT);
        addSelectedButton(EXIT_BUTTON_TEXT);
        break;
    case RESTART_MENU:
        addLogo();
        addButton(RESTART_BUTTON_TEXT);
        addButton(EXIT_BUTTON_TEXT);
        break;
    case RESTART_MENU_RESTART_SELECTED:
        addLogo();
        addSelectedButton(RESTART_BUTTON_TEXT);
        addButton(EXIT_BUTTON_TEXT);
        break;
    case RESTART_MENU_EXIT_SELECTED:
        addLogo();
        addButton(RESTART_BUTTON_TEXT);
        addSelectedButton(EXIT_BUTTON_TEXT);
        break;
    default:
        break;
    }
    refresh();
}
void Display::showNameInput(int state) {
    if (state == NAME_INPUT_1) clear();
    switch (state) {
    case NAME_INPUT_1:
        addLogo();
        addLine(arr, "Player 1: \n");
        refresh();
        break;
    case NAME_INPUT_2:
        addLine(arr, "Player 2: \n");
        refresh();
        break;
    default:
        break;
    }
}
void Display::showBoard() {
    clear();
    addLogo();
    addBoard();
    refresh();
}
void Display::showScores() {
    clear();
    addLogo();
    addScores();
    refresh();
}
void Display::shellCommand(int command) {
    switch (command) {
    case CLEAR:
        #ifdef _WIN32
        system("cls");
        #elif __linux__
        system("clear");
        #elif __APPLE__
        system("clear");
        #else
        std::cerr << "Unsupported OS" << std::endl;
        exit(1);
        #endif
        break;
    case PAUSE:
        #ifdef _WIN32
        system("pause");
        #elif __linux__
        system("read -n1 -r -p \"Press any key to continue . . .\" && echo");
        #elif __APPLE__
        system("read -n1 -r -p \"Press any key to continue . . .\" && echo");
        #else
        std::cerr << "Unsupported OS" << std::endl;
        exit(1);
        #endif
        break;
    case UTF8:
        #ifdef _WIN32
        system("chcp 65001");
        #elif __linux__
        // Nothing needed — terminal is usually UTF-8
        #elif __APPLE__
        // Nothing needed — terminal is usually UTF-8
        #else
        std::cerr << "Unsupported OS" << std::endl;
        exit(1);
        #endif
        break;
    default:
        break;
    }
}


void Display::addLine(std::vector<std::string>& arr, const std::string& newLine) {
    arr.push_back(newLine);
}
void Display::addLogo(){
    addLine(arr, "\n");
    addLine(arr, LOGO_1);
    addLine(arr, LOGO_2);
    addLine(arr, LOGO_3);
    addLine(arr, LOGO_4);
    addLine(arr, LOGO_5);
    addLine(arr, LOGO_6);
}
void Display::addButton(std::string buttonText) {
    addLine(arr, BUTTON_TEMPLATE_1);
    addLine(arr, BUTTON_TEMPLATE_2);
    addLine(arr, std::format(BUTTON_TEMPLATE_3, buttonText));
    addLine(arr, BUTTON_TEMPLATE_4);
}
void Display::addSelectedButton(std::string buttonText) {
    addLine(arr, SELECTED_BUTTON_TEMPLATE_1);
    addLine(arr, SELECTED_BUTTON_TEMPLATE_2);
    addLine(arr, std::format(SELECTED_BUTTON_TEMPLATE_3, buttonText));
    addLine(arr, SELECTED_BUTTON_TEMPLATE_4);
}
void Display::addBoard(){
    addLine(arr,  std::format("\n{} (\u001b[31m●\u001b[36m) Score [{}]  -  {} (\u001b[33m●\u001b[36m) Score [{}]\n\n", player1->getName(), player1->getScore(), player2->getName(), player2->getScore()));
    addLine(arr,  std::format("\t\t\t\t\t\t\tTurn: {}\n", getCurrentPlayersName(player)));
    addLine(arr,              "\t\t\t\t\t _________________________________________\n");
    for (int i = 0; i < BOARD_SIZE; i += 7) {
        addLine(arr,                "\t\t\t\t\t|     |     |     |     |     |     |     |\n");
        addLine(arr, std::format(   "\t\t\t\t\t|  {}  |  {}  |  {}  |  {}  |  {}  |  {}  |  {}  |\n", translateBoard(board[i]), translateBoard(board[i+1]), translateBoard(board[i+2]), translateBoard(board[i+3]), translateBoard(board[i+4]), translateBoard(board[i+5]), translateBoard(board[i+6])));
        addLine(arr,                "\t\t\t\t\t|_____|_____|_____|_____|_____|_____|_____|\n");
    }
    addLine(arr, "\n\t\t\t\t\t ");
    addLine(arr, std::format("  {}     {}     {}     {}     {}     {}     {}   ", board_selector[0], board_selector[1], board_selector[2], board_selector[3], board_selector[4], board_selector[5], board_selector[6]));
    addLine(arr, "\n\n");
}
void Display::addScores(){
    for (int i = 0; i < HIGH_SCORE_FILE_ARRAY_SIZE; i++){
        addLine(arr, "\t\t\t                |\n");
        addLine(arr, std::format("\t\t\t    {}\t|       {}\n", High_Scores[i].getName(), High_Scores[i].getScore()));
        if(i != HIGH_SCORE_FILE_ARRAY_SIZE - 1)
            addLine(arr, "\t\t\t________________|________________\n");
        else
            addLine(arr, "\t\t\t                |\n");
    }
}
std::string Display::translateBoard(int n){
    switch (n) {
        case 1:
            return "\u001b[31m●\u001b[36m"; // Red
        case 2:
            return "\u001b[33m●\u001b[36m"; // Yellow
        case 0:
        default:
            return " ";                     // Empty
    }
}
void Display::clear() { arr.clear(); }
void Display::print(std::string str){std::cout << "\u001b[36m" << str;}
#include "../include/Menus.hpp"

void Menus::select(int menu){
    switch (menu) {
    case START:
        Display::showMenu(START_MENU);
        MenuNavigation::Nav(START_MENU_START_SELECTED, START_MENU_EXIT_SELECTED);
        switch (selector) {
        case '1':
            Menus::select(NAME);
            break;
        case '2':
            exitProgram();
        default:
            break;
        }
        break;
    case NAME:
        Display::showNameInput(NAME_INPUT_1);
        getline(std::cin, lineInput);
        player1->setName(lineInput);
        if(player1->isEmpty())
            player1->setName("Player 1");
        Display::showNameInput(NAME_INPUT_2);
        getline(std::cin, lineInput);
        player2->setName(lineInput);
        if(player2->isEmpty())
            player2->setName("Player 2");
        Menus::select(GAME);
        break;
    case GAME:
        selector = 0;
        Display::showBoard();
        GameNavigation::Nav();
        switch (isEven(player)){
        case 1:
            board[selector - 1] = 1;
            break;
        case 2:
            board[selector - 1] = 2;
        default:
            break;
        }
        Display::showBoard();
        Connect4::gravitySim(&board[selector - 1]);
        GameNavigation::checkFullColumns();
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
    case WIN:
        std::cout << "\t\t\t\t\t\t    " << getCurrentPlayersName(player) << " Wins!\n";
        switch (isEven(player)){
        case 1:
            player1->incScore();
            break;
        case 2:
            player2->incScore();
        default:
            break;
        }
        Display::shellCommand(PAUSE);
        Menus::select(RESTART);
        break;
    case DRAW:
        std::cout << "\t\t\t\t\t\tGame is a Draw!\n";
        Display::shellCommand(PAUSE);
        Menus::select(RESTART);
        break;
    case RESTART:
        Display::showMenu(RESTART_MENU);
        MenuNavigation::Nav(RESTART_MENU_RESTART_SELECTED, RESTART_MENU_EXIT_SELECTED);
        switch (selector) {
        case '1':
            Connect4::initGame();
            Menus::select(GAME);
            break;
        case '2':
            Menus::select(HIGH_SCORES);
        default:
            break;
        }
        break;
    case HIGH_SCORES:
        Scores::refreshHighScores();
        Display::showScores();
        Display::shellCommand(PAUSE);
        exitProgram();
        break;
    default:
        std::cout << "\nMissing Screen\n";
        break;
    }
}

[[noreturn]] void exitProgram(){
    Scores::saveHighScores();
    exit(0);
}
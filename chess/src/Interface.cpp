#include "Interface.h"
#include <iostream>

Interface::Interface(Board& b) : board(b), parser(b) {};

void Interface::show_if()
{
    while (true)
    {
        std::string move;
        board.print_board();
        std::cin >> move;

        parser.makeMove(move);
    }
}
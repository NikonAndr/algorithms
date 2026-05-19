#include "Interface.h"
#include <iostream>

Interface::Interface(Board& b) : board(b), parser(b) {};

void Interface::show_if()
{
    while (true)
    {
        std::string move;
        board.print_board();

        if (debug)
        {
            std::cout << "canCastleKingside(WHITE): " << board.canCastleKingside(WHITE) << "\n";
            
            std::cout << "canCastleKingside(BLACK): " << board.canCastleKingside(BLACK) << "\n";

            std::cout << "canCastleQueenside(WHITE): " << board.canCastleQueenside(WHITE) << "\n";

            std::cout << "canCastleQueenside(BLACK): " << board.canCastleQueenside(BLACK) << "\n";

            std::cout << "hasEnPassant: " << board.hasEnPassant() << "\n";

            if (board.hasEnPassant())
            {
                std::cout << "getEnPassantSquare: {" << board.getEnPassantSquare().first << 
                    ", " << board.getEnPassantSquare().second << "}\n";
            }

            std::cout << "getHalfMoveClock: " << board.getHalfMoveClock() << "\n";
        }
        std::cout << "(" << (board.getCurrentTurn() == WHITE ? "WHITE" : "BLACK" ) << "): ";
        std::cin >> move;

        parser.makeMove(move);
    }
}
#include "Interface.h"
#include <iostream>

#include <chrono>
#include <thread>

Interface::Interface(Board& b, AI bot, AI bot2) : board(b), parser(b), AIbot(bot), AIbot2(bot2) {};

void Interface::show_if()
{
    while (true)
    {
        if (board.isCheckmate(board.getCurrentTurn()))
        {
            board.print_board();
            Color winner = board.getCurrentTurn() == WHITE ? BLACK : WHITE;

            std::cout << (winner == WHITE ? "WHITE" : "BLACK") << " wins by checkmate!\n";
            break;
        }

        if (board.isStalemate(board.getCurrentTurn()))
        {
            board.print_board();
            std::cout << "Stalemate! Draw!\n";
            break;
        }

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

        if (!against_ai && !ai_against_ai)
        {
            std::cout << "(" << (board.getCurrentTurn() == WHITE ? "WHITE" : "BLACK" ) << "): ";

            std::string move;
            std::cin >> move;

            parser.makeMove(move);
        }
        else if (against_ai)
        {
            Color current = board.getCurrentTurn();

            if (current == AIbot.getAIColor())
            {
                Move m = AIbot.getBestMove(board);
                board.makeMove(m);
            }
            else 
            {
                std::cout << "(" << (board.getCurrentTurn() == WHITE ? "WHITE" : "BLACK" ) << "): ";

                std::string move;
                std::cin >> move;

                parser.makeMove(move);
            }
        }
        else
        {
            if (AIbot.getAIColor() == AIbot2.getAIColor())
            {
                throw std::runtime_error("[Interface] both ai are the same color");
            }

            Color current = board.getCurrentTurn();

            if (current == AIbot.getAIColor())
            {
                Move m = AIbot.getBestMove(board);
                board.makeMove(m);
            }
            else
            {
                Move m = AIbot2.getBestMove(board);
                board.makeMove(m);
            }

            std::this_thread::sleep_for(std::chrono::nanoseconds(10));
            std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
        }

    }
}
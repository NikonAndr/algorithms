#include "Board.h"

#include <iostream>
#include <exception>

Board::Board()
{
    init_board();
}

void Board::init_board()
{
    board[0] = {{ {ROOK, BLACK},{KNIGHT, BLACK}, {BISHOP, BLACK}, {QUEEN, BLACK}, 
    {KING, BLACK}, {BISHOP, BLACK}, {KNIGHT, BLACK},{ROOK, BLACK} }};

    board[7] = {{ {ROOK, WHITE}, {KNIGHT, WHITE}, {BISHOP, WHITE}, {QUEEN, WHITE}, 
    {KING, WHITE}, {BISHOP, WHITE}, {KNIGHT, WHITE},{ROOK, WHITE} }};

    for (Piece& p : board[1])
    {
        p.type = PAWN;
        p.color = BLACK;
    }

    for (Piece& p : board[6])
    {
        p.type = PAWN;
        p.color = WHITE;
    }
}

void Board::print_board()
{
    static const char* W[] = {" ", "♙", "♘", "♗", "♖", "♕", "♔"};
    static const char* B[] = {"", "♟", "♞", "♝", "♜", "♛", "♚"};

    for (int i = 0; i < 8; i++)
    {
        for (Piece& p : board[i])
        {
            if (p.type == EMPTY)
            {
                std::cout << " ";
            }
            else
            {
                if (p.color != WHITE && p.color != BLACK)
                {
                    throw std::runtime_error("Piece type is not EMPTY, neighter WHITE or BLACK");
                }
                std::cout << (p.color == WHITE ? W[p.type] : B[p.type]);
            }
        }
        std::cout << "\n";
    }
}

#include "MoveGenerator.h"
#include <iostream>

std::vector<Move> getLegalMoves(const Board& board, int row, int col)
{
    Piece p = board.getPiece(row, col);

    //debug
    //std::cout << "\n" << p.color << " " << p.type << " " << board.map_position(row, col) << "\n" ;
    
    const auto& b = board.get_board();
    std::vector<Move> legal_moves;

    if (p.type == PAWN)
    {
        int dir = (p.color == WHITE) ? -1 : 1;
        int startRow = (p.color == WHITE) ? 6 : 1;
        Color enemy = (p.color == WHITE) ? BLACK : WHITE;

        int nextRow = row + dir;
        int jumpRow = row + 2*dir;
        int leftColumn = col - 1;
        int rightColumn = col + 1;
        
        //move 1 space 
        if(nextRow >= 0 && nextRow < 8 && 
            b[nextRow][col].type == EMPTY
        )
        {
            legal_moves.push_back({row, col, nextRow, col});
        }

        //move 2 spaces
        if(jumpRow >= 0 && jumpRow < 8 &&
            row == startRow && 
            b[nextRow][col].type == EMPTY &&
            b[jumpRow][col].type == EMPTY
        )
        {
            legal_moves.push_back({row, col, jumpRow, col});
        }

        //side attack
        if (nextRow >= 0 && nextRow < 8 && 
            col > 0 && 
            b[nextRow][leftColumn].type != EMPTY &&
            b[nextRow][leftColumn].color == enemy
        )
        {
            legal_moves.push_back({row, col, nextRow, leftColumn});
        }
        if (nextRow >= 0 && nextRow < 8 &&
            col < 7 &&
            b[nextRow][rightColumn].type != EMPTY &&
            b[nextRow][rightColumn].color == enemy
        )
        {
            legal_moves.push_back({row, col, nextRow, rightColumn});
        }
    }

    return legal_moves;
}


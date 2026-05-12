#pragma once 
#include "Piece.h"
#include <array>

class Board
{
private:
    std::array<std::array<Piece, 8>, 8> board;

    Color currentTurn = NONE;
    bool whiteKingsSideCastle = true;
    bool blackKingsSideCastle = true;
    int enPassantCol = -1;
    int enPassantRow = 1;
    int halfMoveClock = -1;


    void init_board();
public:
    Board();
    void print_board();
};
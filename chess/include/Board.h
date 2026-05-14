#pragma once 
#include "Move.h"
#include <array>
#include <string>

class Board
{
private:
    std::array<std::array<Piece, 8>, 8> board;

    Color currentTurn = WHITE;
    bool whiteKingsSideCastle = true;
    bool blackKingsSideCastle = true;
    int enPassantCol = -1;
    int enPassantRow = -1;
    int halfMoveClock = 0;


    void init_board();
public:
    Board();
    void print_board();

    std::string map_position(int row, int col) const;

    Piece getPiece(int row, int col) const;

    const std::array<std::array<Piece, 8>, 8>& get_board() const;

    bool makeMove(const Move& move);

};
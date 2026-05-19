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
    bool whiteQueensSideCastle = true;
    bool blackQueensSideCastle = true;
    int enPassantCol = -1;
    int enPassantRow = -1;
    int halfMoveClock = 0;


    void init_board();
public:
    Board(bool castle_test = false, bool promotion_test = false);
    void print_board();

    std::string map_position(int row, int col) const;

    Piece getPiece(int row, int col) const;

    const std::array<std::array<Piece, 8>, 8>& get_board() const;

    bool makeMove(const Move& move);

    bool isSquareAttacked(int row, int col, Color byColor) const;

    bool isInCheck(Color color) const;

    bool isCheckmate(Color color) const;
    bool isStalemate(Color color) const;

    //getters
    bool canCastleKingside(Color color) const;
    bool canCastleQueenside(Color color) const;
    bool hasEnPassant() const;
    std::pair<int, int> getEnPassantSquare() const;
    int getHalfMoveClock() const;
    Color getCurrentTurn() const;

    bool castle_test = false;
    bool promotion_test = false;

};
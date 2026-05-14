#pragma once 

#include "Piece.h"

struct Move
{
    int fromRow, fromCol;
    int toRow, toCol;
    Figure promotion = EMPTY;
    bool isCastle = false;
    bool isEnPassant = false;

    bool operator==(const Move& o) const {
        return fromRow == o.fromRow && fromCol == o.fromCol
        && toRow == o.toRow && toCol == o.toCol 
        && promotion == o.promotion && isCastle == o.isCastle
        && isEnPassant == o.isEnPassant;
    }
};

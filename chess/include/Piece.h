#pragma once

enum Figure {EMPTY, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING};
enum Color {WHITE, BLACK, NONE};

struct Piece
{
    Figure type = EMPTY;
    Color color = NONE;
};

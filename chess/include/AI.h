#pragma once 
#include "Board.h"
#include "Move.h"

class AI
{
private:
    Color aiColor;
    int searchDepth;

    int evaluate(const Board& board) const;
    int minimax(Board board, int depth, int alpha, int beta, bool maximizing) const;

    // piece-square tables 
    static const int pawnTable[8][8];
    static const int knightTable[8][8];
    static const int bishopTable[8][8];
    static const int rookTable[8][8];
    static const int queenTable[8][8];
    static const int kingMiddleTable[8][8];
    static const int kingEndTable[8][8];

    int pieceValue(Figure f) const;
    int pstScore(Figure f, int row, int col, Color color, bool endgame) const;
    bool isEndgame(const Board& board) const;

public:
    AI(Color color, int depth = 3);
    Move getBestMove(Board& board) const;
    Color getAIColor() const;
};
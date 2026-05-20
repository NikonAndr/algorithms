#include "AI.h"
#include "MoveGenerator.h"

#include <vector>
#include <limits>

int AI::pieceValue(Figure f) const
{
    switch(f)
    {
        case EMPTY: return 0; 
        case PAWN: return 100; 
        case KNIGHT: return 320; 
        case BISHOP: return 330;
        case ROOK: return 500;
        case QUEEN: return 900;
        case KING: return 20000;
        default: return 0;
    }
}

 // piece-square tables 
const int AI::pawnTable[8][8] = {
    {  0,  0,  0,  0,  0,  0,  0,  0 },
    { 50, 50, 50, 50, 50, 50, 50, 50 },
    { 10, 10, 20, 30, 30, 20, 10, 10 },
    {  5,  5, 10, 25, 25, 10,  5,  5 },
    {  0,  0,  0, 20, 20,  0,  0,  0 },
    {  5, -5,-10,  0,  0,-10, -5,  5 },
    {  5, 10, 10,-20,-20, 10, 10,  5 },
    {  0,  0,  0,  0,  0,  0,  0,  0 }
};

const int AI::knightTable[8][8] = {
    {-50,-40,-30,-30,-30,-30,-40,-50},
    {-40,-20,  0,  0,  0,  0,-20,-40},
    {-30,  0, 10, 15, 15, 10,  0,-30},
    {-30,  5, 15, 20, 20, 15,  5,-30},
    {-30,  0, 15, 20, 20, 15,  0,-30},
    {-30,  5, 10, 15, 15, 10,  5,-30},
    {-40,-20,  0,  5,  5,  0,-20,-40},
    {-50,-40,-30,-30,-30,-30,-40,-50}
};

const int AI::bishopTable[8][8] = {
    {-20,-10,-10,-10,-10,-10,-10,-20},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-10,  0,  5, 10, 10,  5,  0,-10},
    {-10,  5,  5, 10, 10,  5,  5,-10},
    {-10,  0, 10, 10, 10, 10,  0,-10},
    {-10, 10, 10, 10, 10, 10, 10,-10},
    {-10,  5,  0,  0,  0,  0,  5,-10},
    {-20,-10,-10,-10,-10,-10,-10,-20}
};

const int AI::rookTable[8][8] = {
    {  0,  0,  0,  0,  0,  0,  0,  0},
    {  5, 10, 10, 10, 10, 10, 10,  5},
    { -5,  0,  0,  0,  0,  0,  0, -5},
    { -5,  0,  0,  0,  0,  0,  0, -5},
    { -5,  0,  0,  0,  0,  0,  0, -5},
    { -5,  0,  0,  0,  0,  0,  0, -5},
    { -5,  0,  0,  0,  0,  0,  0, -5},
    {  0,  0,  0,  5,  5,  0,  0,  0}
};

const int AI::queenTable[8][8] = {
    {-20,-10,-10, -5, -5,-10,-10,-20},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-10,  0,  5,  5,  5,  5,  0,-10},
    { -5,  0,  5,  5,  5,  5,  0, -5},
    {  0,  0,  5,  5,  5,  5,  0, -5},
    {-10,  5,  5,  5,  5,  5,  0,-10},
    {-10,  0,  5,  0,  0,  0,  0,-10},
    {-20,-10,-10, -5, -5,-10,-10,-20}
};

const int AI::kingMiddleTable[8][8] = {
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-20,-30,-30,-40,-40,-30,-30,-20},
    {-10,-20,-20,-20,-20,-20,-20,-10},
    { 20, 20,  0,  0,  0,  0, 20, 20},
    { 20, 30, 10,  0,  0, 10, 30, 20}
};

const int AI::kingEndTable[8][8] = {
    {-50,-40,-30,-20,-20,-30,-40,-50},
    {-30,-20,-10,  0,  0,-10,-20,-30},
    {-30,-10, 20, 30, 30, 20,-10,-30},
    {-30,-10, 30, 40, 40, 30,-10,-30},
    {-30,-10, 30, 40, 40, 30,-10,-30},
    {-30,-10, 20, 30, 30, 20,-10,-30},
    {-30,-30,  0,  0,  0,  0,-30,-30},
    {-50,-30,-30,-30,-30,-30,-30,-50}
};

int AI::pstScore(Figure f, int row, int col, Color color, bool endgame) const
{
    if (color == BLACK) 
        row = 7 - row;

    switch(f)
    {
        case EMPTY: return 0; 
        case PAWN: 
        {
            return pieceValue(f) + pawnTable[row][col];
        }
        case KNIGHT: 
        {
            return pieceValue(f) + knightTable[row][col];
        }
        case BISHOP: 
        {
            return pieceValue(f) + bishopTable[row][col];
        }
        case ROOK: 
        {
            return pieceValue(f) + rookTable[row][col];
        }
        case QUEEN: 
        {
            return pieceValue(f) + queenTable[row][col];
        }
        case KING: 
        {
            return pieceValue(f) + 
                (endgame ? kingEndTable[row][col] :kingMiddleTable[row][col]);
        }
        default: return 0;
    }
}

bool AI::isEndgame(const Board& board) const
{
    int total_score = 0;

    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            Piece p = board.getPiece(r, c);

            if (p.type == KING || p.type == PAWN)
                continue;
            
            total_score += pieceValue(p.type);
        }
    }

    return (total_score < 1300 ? true : false);
}

int AI::evaluate(const Board& board) const
{
    int ai_score = 0;
    bool endgame = isEndgame(board);

    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            Piece p = board.getPiece(r, c);

            if (p.type == EMPTY)
                continue;

            if (p.color == aiColor)
                ai_score += pstScore(p.type, r, c, aiColor, endgame);
            else 
                ai_score -= pstScore(p.type, r, c, p.color, endgame);
        }
    }

    return ai_score;
}

int AI::minimax(Board board, int depth, int alpha, int beta, bool maximizing) const
{
    if (depth == 0)
        return evaluate(board);
    
    Color current = board.getCurrentTurn();
    
    if (board.isCheckmate(current))
        return maximizing ? -100000 : 100000;
    
    if (board.isStalemate(current))
        return 0;

    std::vector<Move> allMoves;
    
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            Piece p = board.getPiece(r, c);

            if (p.color == current)
            {
                const auto legal_moves = getLegalMoves(board, r, c);

                allMoves.insert(allMoves.end(), legal_moves.begin(), legal_moves.end());
            }
        }
    }

    if (maximizing)
    {
        int best = std::numeric_limits<int>::min();
        for (const auto& move : allMoves)
        {
            Board next = board;
            if(!next.makeMove(move)) continue;
            int score = minimax(next, depth - 1, alpha, beta, !maximizing);

            if (best < score)
                best = score;

            alpha = std::max(alpha, best);
            if (beta <= alpha)
                break;
        }

        return best; 
    }
    //minimizing
    else
    {
        int best = std::numeric_limits<int>::max();
        for (const auto& move : allMoves)
        {
            Board next = board;
            if(!next.makeMove(move)) continue;
            int score = minimax(next, depth - 1, alpha, beta, maximizing);

            if (best > score)
                best = score;

            beta = std::min(beta, best);
            if (beta <= alpha)
                break;
        }

        return best; 
    }
}

Move AI::getBestMove(Board& board) const
{
    int min = std::numeric_limits<int>::min();
    int max = std::numeric_limits<int>::max();

    std::vector<Move> allMoves;
    
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            Piece p = board.getPiece(r, c);

            if (p.color == aiColor)
            {
                const auto legal_moves = getLegalMoves(board, r, c);

                allMoves.insert(allMoves.end(), legal_moves.begin(), legal_moves.end());
            }
        }
    }

    int best_score = min;
    Move best_move = {-1, -1, -1, -1};

    for (const auto& move : allMoves)
    {
        Board next = board;
        if(!next.makeMove(move)) continue;
        int score = minimax(next, searchDepth - 1, min, max, false);

        if (best_score < score)
        {
            best_score = score;
            best_move = move;
        }
    }

    return best_move;
}

AI::AI(Color color, int depth) : aiColor(color), searchDepth(depth) {}

Color AI::getAIColor() const
{
    return aiColor;
}
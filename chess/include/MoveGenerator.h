#pragma once
#include "Board.h"
#include "Move.h"

#include <string>
#include <vector>

bool isKingsideCastleLegal(Color color, const Board& board);

bool isQueensideCastleLegal(Color color, const Board& board);

std::vector<Move> getLegalMoves(const Board& board, int row, int col);

std::vector<Move> getAttackMoves(const Board& board, int row, int col);

#pragma once
#include "Board.h"
#include "Move.h"

#include <string>
#include <vector>

std::vector<Move> getLegalMoves(const Board& board, int row, int col);

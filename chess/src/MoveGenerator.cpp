#include "MoveGenerator.h"
#include <iostream>

bool isKingsideCastleLegal(Color color, const Board& board)
{
    const auto& b = board.get_board();

    if (color == WHITE)
    {
        if (board.canCastleKingside(WHITE) &&
            b[7][5].type == EMPTY &&
            b[7][6].type == EMPTY &&
            b[7][7].type == ROOK &&
            b[7][7].color == WHITE &&
            !board.isInCheck(WHITE) &&
            !board.isSquareAttacked(7, 5, BLACK) &&
            !board.isSquareAttacked(7, 6, BLACK))
        {
            return true;
        }
    }

    if (color == BLACK)
    {
        if (board.canCastleKingside(BLACK) &&
            b[0][5].type == EMPTY &&
            b[0][6].type == EMPTY &&
            b[0][7].type == ROOK &&
            b[0][7].color == BLACK &&
            !board.isInCheck(BLACK) &&
            !board.isSquareAttacked(0, 5, WHITE) &&
            !board.isSquareAttacked(0, 6, WHITE))
        {
            return true;
        }
    }

    return false;
}

bool isQueensideCastleLegal(Color color, const Board& board)
{
    const auto& b = board.get_board();

    if (color == WHITE)
    {
        if (board.canCastleQueenside(WHITE) &&
            b[7][1].type == EMPTY &&
            b[7][2].type == EMPTY &&
            b[7][3].type == EMPTY &&
            b[7][0].type == ROOK &&
            b[7][0].color == WHITE &&
            !board.isInCheck(WHITE) &&
            !board.isSquareAttacked(7, 2, BLACK) &&
            !board.isSquareAttacked(7, 3, BLACK)) 
        {
            return true;
        }
    }

    if (color == BLACK)
    {
        if (board.canCastleQueenside(BLACK) &&
            b[0][1].type == EMPTY &&
            b[0][2].type == EMPTY &&
            b[0][3].type == EMPTY &&
            b[0][0].type == ROOK &&
            b[0][0].color == BLACK &&
            !board.isInCheck(BLACK) &&
            !board.isSquareAttacked(0, 2, WHITE) &&
            !board.isSquareAttacked(0, 3, WHITE))
        {
            return true;
        }
    }

    return false;
}

std::vector<Move> getLegalMoves(const Board& board, int row, int col)
{
    Piece p = board.getPiece(row, col);

    //debug
    //std::cout << "\n" << p.color << " " << p.type << " " << board.map_position(row, col) << "\n" ;
    
    const auto& b = board.get_board();
    std::vector<Move> legal_moves;

    if (p.type == EMPTY)
    {
        std::cout << "empty cell!\n";
        return legal_moves;
    }

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

        //enPassant
        std::pair<int,int> enPassantSquare = board.getEnPassantSquare();

        if (enPassantSquare != std::pair<int,int>{-1,-1})
        {
            int epRow = enPassantSquare.first;
            int epCol = enPassantSquare.second;

            //left enPassant
            if (col > 0 &&
                nextRow == epRow &&
                leftColumn == epCol)
            {
                Piece target = board.getPiece(row, leftColumn);

                if (target.type == PAWN && target.color == enemy)
                {
                    legal_moves.push_back({row, col, epRow, epCol, EMPTY, false, true});
                }
            }

            //right enPassant
            if (col < 7 &&
                nextRow == epRow
                && rightColumn == epCol)
            {
                Piece target = board.getPiece(row, rightColumn);

                if (target.type == PAWN && target.color == enemy)
                {
                    legal_moves.push_back({row, col, epRow, epCol, EMPTY, false, true});
                }
            }
        }
    }
    else if (p.type == KNIGHT)
    {
        static const std::pair<int,int> deltas[] 
        {
            {-2,-1}, {-2, 1},
            {-1, -2}, {-1, 2},
            {1, -2}, {1, 2},
            {2, -1}, {2, 1}
        };

        for (const auto& d : deltas)
        {
            int nextRow = row + d.first;
            int nextCol = col + d.second;

            //validate position 
            if (nextRow >= 0 && nextRow < 8 
            && nextCol >= 0 && nextCol < 8)
            {
                Piece target = board.getPiece(nextRow, nextCol);

                //validate color
                if (target.color != p.color)
                {
                    legal_moves.push_back({row, col, nextRow, nextCol});
                }
            }
        }
    }
    else if (p.type == BISHOP)
    {
        static const std::pair<int, int> dirs[] 
        {
            {-1, -1}, {-1, 1},
            {1, -1}, {1, 1}
        };

        for (const auto& d : dirs)
        {
            int nextRow = row + d.first;
            int nextCol = col + d.second;

            while (nextRow >= 0 && nextRow < 8
            && nextCol >= 0 && nextCol < 8)
            {
                Piece target = board.getPiece(nextRow, nextCol);

                if (target.type == EMPTY)
                {
                    legal_moves.push_back({row, col, nextRow, nextCol});
                }
                else 
                {
                    if (target.color != p.color)
                    {
                        legal_moves.push_back({row, col, nextRow, nextCol});
                    }
                    break;
                }

                nextRow += d.first;
                nextCol += d.second;
            }
        }
    }
    else if (p.type == ROOK)
    {
        static const std::pair<int, int> dirs[] 
        {
            {-1, 0}, {0, -1},
            {1, 0}, {0, 1}
        };

        for (const auto& d : dirs)
        {
            int nextRow = row + d.first;
            int nextCol = col + d.second;

            while (nextRow >= 0 && nextRow < 8
            && nextCol >= 0 && nextCol < 8)
            {
                Piece target = board.getPiece(nextRow, nextCol);

                if (target.type == EMPTY)
                {
                    legal_moves.push_back({row, col, nextRow, nextCol});
                }
                else 
                {
                    if (target.color != p.color)
                    {
                        legal_moves.push_back({row, col, nextRow, nextCol});
                    }
                    break;
                }

                nextRow += d.first;
                nextCol += d.second;
            }
        }
    }
    else if (p.type == QUEEN)
    {
        static const std::pair<int, int> dirs[] 
        {
            {-1, 0}, {0, -1},
            {1, 0}, {0, 1},
            {-1, -1}, {-1, 1},
            {1, -1}, {1, 1}
        };

        for (const auto& d : dirs)
        {
            int nextRow = row + d.first;
            int nextCol = col + d.second;

            while (nextRow >= 0 && nextRow < 8
            && nextCol >= 0 && nextCol < 8)
            {
                Piece target = board.getPiece(nextRow, nextCol);

                if (target.type == EMPTY)
                {
                    legal_moves.push_back({row, col, nextRow, nextCol});
                }
                else 
                {
                    if (target.color != p.color)
                    {
                        legal_moves.push_back({row, col, nextRow, nextCol});
                    }
                    break;
                }

                nextRow += d.first;
                nextCol += d.second;
            }
        }
    }
    else if (p.type == KING)
    {
        static const std::pair<int,int> deltas[] 
        {
            {-1,0}, {-1,-1}, {-1, 1},
            {1, -1}, {1, 0}, {1,1},
            {0, -1}, {0, 1}
        };

        for (const auto& d : deltas)
        {
            int nextRow = row + d.first;
            int nextCol = col + d.second;

            //validate position 
            if (nextRow >= 0 && nextRow < 8 
            && nextCol >= 0 && nextCol < 8)
            {
                Piece target = board.getPiece(nextRow, nextCol);

                //validate color
                if (target.color != p.color)
                {
                    legal_moves.push_back({row, col, nextRow, nextCol});
                }
            }
        }

        //castle

        if (p.color == WHITE && row == 7 && col == 4)
        {
            //white kingside
            if (isKingsideCastleLegal(WHITE, board))
            {
                legal_moves.push_back({row, col, row, col + 2, EMPTY, true});
            }

            //white queenside
            if (isQueensideCastleLegal(WHITE, board))
            {
                legal_moves.push_back({row, col, row, col - 2, EMPTY, true});
            }
        }

        if (p.color == BLACK && row == 0 && col == 4)
        {
            //black kingside
            if (isKingsideCastleLegal(BLACK, board))
            {
                legal_moves.push_back({row, col, row, col + 2, EMPTY, true});
            }

            //black queenside
            if(isQueensideCastleLegal(BLACK, board))
            {
                legal_moves.push_back({row, col, row, col - 2, EMPTY, true});
            }
        }
    }

    return legal_moves;
}


std::vector<Move> getAttackMoves(const Board& board, int row, int col)
{
    Piece p = board.getPiece(row, col);
    
    std::vector<Move> attack_moves;

    if (p.type == EMPTY)
    {
        return attack_moves;
    }

    if (p.type == PAWN)
    {
        int dir = p.color == WHITE ? -1 : 1;

        if (row + dir >= 0 && row + dir < 8)
        {
            if (col + 1 >= 0 && col + 1 < 8)
                attack_moves.push_back({row, col, row + dir, col + 1});

            if (col - 1 >= 0 && col - 1 < 8)
                attack_moves.push_back({row, col, row + dir, col - 1});
        }
    }
    else if (p.type == KNIGHT)
    {
        static const std::pair<int,int> deltas[] 
        {
            {-2,-1}, {-2, 1},
            {-1, -2}, {-1, 2},
            {1, -2}, {1, 2},
            {2, -1}, {2, 1}
        };

        for (const auto& d : deltas)
        {
            int nextRow = row + d.first;
            int nextCol = col + d.second;

            //validate position 
            if (nextRow >= 0 && nextRow < 8 
            && nextCol >= 0 && nextCol < 8)
            {
                Piece target = board.getPiece(nextRow, nextCol);

                //validate color
                if (target.color != p.color)
                {
                    attack_moves.push_back({row, col, nextRow, nextCol});
                }
            }
        }
    }
    else if (p.type == BISHOP)
    {
        static const std::pair<int, int> dirs[] 
        {
            {-1, -1}, {-1, 1},
            {1, -1}, {1, 1}
        };

        for (const auto& d : dirs)
        {
            int nextRow = row + d.first;
            int nextCol = col + d.second;

            while (nextRow >= 0 && nextRow < 8
            && nextCol >= 0 && nextCol < 8)
            {
                Piece target = board.getPiece(nextRow, nextCol);

                if (target.type == EMPTY)
                {
                    attack_moves.push_back({row, col, nextRow, nextCol});
                }
                else 
                {
                    if (target.color != p.color)
                    {
                        attack_moves.push_back({row, col, nextRow, nextCol});
                    }
                    break;
                }

                nextRow += d.first;
                nextCol += d.second;
            }
        }
    }
    else if (p.type == ROOK)
    {
        static const std::pair<int, int> dirs[] 
        {
            {-1, 0}, {0, -1},
            {1, 0}, {0, 1}
        };

        for (const auto& d : dirs)
        {
            int nextRow = row + d.first;
            int nextCol = col + d.second;

            while (nextRow >= 0 && nextRow < 8
            && nextCol >= 0 && nextCol < 8)
            {
                Piece target = board.getPiece(nextRow, nextCol);

                if (target.type == EMPTY)
                {
                    attack_moves.push_back({row, col, nextRow, nextCol});
                }
                else 
                {
                    if (target.color != p.color)
                    {
                        attack_moves.push_back({row, col, nextRow, nextCol});
                    }
                    break;
                }

                nextRow += d.first;
                nextCol += d.second;
            }
        }
    }
    else if (p.type == QUEEN)
    {
        static const std::pair<int, int> dirs[] 
        {
            {-1, 0}, {0, -1},
            {1, 0}, {0, 1},
            {-1, -1}, {-1, 1},
            {1, -1}, {1, 1}
        };

        for (const auto& d : dirs)
        {
            int nextRow = row + d.first;
            int nextCol = col + d.second;

            while (nextRow >= 0 && nextRow < 8
            && nextCol >= 0 && nextCol < 8)
            {
                Piece target = board.getPiece(nextRow, nextCol);

                if (target.type == EMPTY)
                {
                    attack_moves.push_back({row, col, nextRow, nextCol});
                }
                else 
                {
                    if (target.color != p.color)
                    {
                        attack_moves.push_back({row, col, nextRow, nextCol});
                    }
                    break;
                }

                nextRow += d.first;
                nextCol += d.second;
            }
        }
    }
    else if (p.type == KING)
    {
        static const std::pair<int,int> deltas[] 
        {
            {-1,0}, {-1,-1}, {-1, 1},
            {1, -1}, {1, 0}, {1,1},
            {0, -1}, {0, 1}
        };

        for (const auto& d : deltas)
        {
            int nextRow = row + d.first;
            int nextCol = col + d.second;

            //validate position 
            if (nextRow >= 0 && nextRow < 8 
            && nextCol >= 0 && nextCol < 8)
            {
                Piece target = board.getPiece(nextRow, nextCol);

                //validate color
                if (target.color != p.color)
                {
                    attack_moves.push_back({row, col, nextRow, nextCol});
                }
            }
        }
    }

    return attack_moves;
}
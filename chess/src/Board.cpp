#include "Board.h"
#include "MoveGenerator.h"


#include <iostream>
#include <exception>
#include <algorithm>

Board::Board()
{
    init_board();
}

void Board::init_board()
{
    board[0] = {{ {ROOK, BLACK},{KNIGHT, BLACK}, {BISHOP, BLACK}, {QUEEN, BLACK}, 
    {KING, BLACK}, {BISHOP, BLACK}, {KNIGHT, BLACK},{ROOK, BLACK} }};

    board[7] = {{ {ROOK, WHITE}, {KNIGHT, WHITE}, {BISHOP, WHITE}, {QUEEN, WHITE}, 
    {KING, WHITE}, {BISHOP, WHITE}, {KNIGHT, WHITE},{ROOK, WHITE} }};

    for (Piece& p : board[1])
    {
        p.type = PAWN;
        p.color = BLACK;
    }

    for (Piece& p : board[6])
    {
        p.type = PAWN;
        p.color = WHITE;
    }
}

void Board::print_board()
{
    static const char* W[] = {" ", "♙", "♘", "♗", "♖", "♕", "♔"};
    static const char* B[] = {" ", "♟", "♞", "♝", "♜", "♛", "♚"};
    static const char* letters[] = {"a", "b", "c", "d", "e", "f", "g", "h"};
    static const char* nums[] = {"1", "2", "3", "4", "5", "6", "7", "8"};
    
    std::cout << "  ";

    for (const char* l : letters)
    {
        std::cout << l;
    }

    std::cout << "\n";

    for (int i = 0; i < 8; i++)
    {
        std::cout << nums[7-i] << " ";
        for (Piece& p : board[i])
        {
            if (p.type == EMPTY)
            {
                std::cout << " ";
            }
            else
            {
                if (p.color != WHITE && p.color != BLACK)
                {
                    throw std::runtime_error("Piece type is not EMPTY, neighter WHITE or BLACK");
                }
                std::cout << (p.color == WHITE ? W[p.type] : B[p.type]);
            }
        }
        std::cout << "\n";
    }
}

std::string Board::map_position(int row, int col) const
{
    static const std::string letters[] = {"a", "b", "c", "d", "e", "f", "g", "h"};
    static const std::string nums[] = {"1", "2", "3", "4", "5", "6", "7", "8"};

    return letters[col] + nums[7 - row];
}

Piece Board::getPiece(int row, int col) const
{
    return board[row][col];
}

const std::array<std::array<Piece, 8>, 8>& Board::get_board() const
{
    return board;
}

bool Board::makeMove(const Move& move)
{
    if (move.fromRow < 0 || move.fromRow >= 8 || move.fromCol < 0 || move.fromCol >= 8)
        return false;

    if (move.toRow < 0 || move.toRow >= 8 || move.toCol < 0 || move.toCol >= 8)
        return false;

    Piece old_p = getPiece(move.fromRow, move.fromCol);

    if (old_p.color != currentTurn)
    {
        std::cout << "illegal move!";
        return false;
    }

    if (old_p.type == EMPTY)
    {
        std::cout << "illegal move!";
        return false;
    }

    //check if move is legal 
    const auto& legal_moves = getLegalMoves(*this, move.fromRow, move.fromCol);

    if (std::find(legal_moves.begin(), legal_moves.end(), move) == legal_moves.end())
    {
        //debug 
        std::cout << "illegal move!\n";
        return false;
    }
    
    //for now just the pawn
    //copy properties of the old_p to the new_p 
    board[move.toRow][move.toCol].color = old_p.color;
    board[move.toRow][move.toCol].type = old_p.type;

    //set old_p as an empty piece
    board[move.fromRow][move.fromCol].color = NONE;
    board[move.fromRow][move.fromCol].type = EMPTY;

    //set current turn to the opposite color
    currentTurn = currentTurn == WHITE ? BLACK : WHITE;

    return true;
}
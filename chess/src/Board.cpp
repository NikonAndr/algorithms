#include "Board.h"
#include "MoveGenerator.h"


#include <iostream>
#include <exception>
#include <algorithm>

Board::Board(bool castle_test, bool promotion_test, bool checkmate_test) : castle_test(castle_test), 
    promotion_test(promotion_test), checkmate_test(checkmate_test)
{
    init_board();
}

void Board::init_board()
{
    if (castle_test)
    {
        board[0] = {{ {ROOK, BLACK},{EMPTY, NONE}, {EMPTY, NONE}, {EMPTY, NONE}, 
        {KING, BLACK}, {EMPTY, NONE}, {EMPTY, NONE},{ROOK, BLACK} }};

        board[7] = {{ {ROOK, WHITE},{EMPTY, NONE}, {EMPTY, NONE}, {EMPTY, NONE}, 
        {KING, WHITE}, {EMPTY, NONE}, {EMPTY, NONE},{ROOK, WHITE} }};
    }
    else if (promotion_test)
    {
        board[0][0] = {KING, BLACK};
        board[7][7] = {KING, WHITE};

        board[1][3] = {PAWN, WHITE};
        board[1][6] = {PAWN, WHITE};
        board[6][7] = {PAWN, BLACK};
    }
    else if (checkmate_test)
    {
        board[0][0] = {KING, BLACK};
        board[7][7] = {KING, WHITE};

        board[7][1] = {QUEEN, WHITE};
        board[3][7] = {ROOK, WHITE};
        board[4][7] = {ROOK, WHITE};
    }
    else
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
                    throw std::runtime_error("[BOARD - print] Piece type is not EMPTY, neighter WHITE or BLACK");
                }
                std::cout << (p.color == WHITE ? W[p.type] : B[p.type]);
            }
        }
        std::cout << " " << nums[7-i] << "\n";
    }

    std::cout << "  ";
    for (const char* l : letters)
    {
        std::cout << l;
    }

    std::cout << "\n";
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

    if (old_p.color != currentTurn || old_p.type == EMPTY)
    {
        std::cout << "illegal move!\n";
        return false;
    }

    //check if move is legal 
    const auto& legal_moves = getLegalMoves(*this, move.fromRow, move.fromCol);

    if (std::find(legal_moves.begin(), legal_moves.end(), move) == legal_moves.end())
    {
        std::cout << "no legal moves!\n";
        std::cout << legal_moves.size() << "\n";
        return false;
    }

    Piece captured = getPiece(move.toRow, move.toCol);

    //en passant - determine column of enemy pawn
    int enPassantColCaptured;
    if (move.isEnPassant)
    {
        enPassantColCaptured = move.fromCol < move.toCol ? move.fromCol + 1 : move.fromCol - 1;
    }

    //check if king is in check after move
    Board temp = *this;

    if (!move.isCastle)
    {
        temp.board[move.toRow][move.toCol] = old_p;
        temp.board[move.fromRow][move.fromCol] = {EMPTY, NONE};

        if (move.isEnPassant)
        {
            temp.board[move.fromRow][enPassantColCaptured] = {EMPTY, NONE};
        }

        if (move.promotion != EMPTY)
        {
            temp.board[move.toRow][move.toCol] = {move.promotion, old_p.color};
        }

        if (temp.isInCheck(old_p.color))
        {
            //std::cout << "King is in check after move!\n";
            return false;
        }
    }

    //copy properties of the old_p to the new_p 
    board[move.toRow][move.toCol] = old_p;
    //set old_p as an empty piece
    board[move.fromRow][move.fromCol] = {EMPTY, NONE}; 

    //castle - move rook
    if (move.isCastle)
    {
        if (old_p.color == WHITE)
        {
            if (move.toCol == 6)
            {
                board[7][5] = {ROOK, WHITE};
                board[7][7] = {EMPTY, NONE};
            }
            else if (move.toCol == 2)
            {
                board[7][3] = {ROOK, WHITE};
                board[7][0] = {EMPTY, NONE};
            }
        }
        else if (old_p.color == BLACK)
        {
            if (move.toCol == 6)
            {
                board[0][5] = {ROOK, BLACK};
                board[0][7] = {EMPTY, NONE};
            }
            else if (move.toCol == 2)
            {
                board[0][3] = {ROOK, BLACK};
                board[0][0] = {EMPTY, NONE};
            }
        }
    }

    //EnPassant - delete enemy pawn
    if (move.isEnPassant)
    {
        board[move.fromRow][enPassantColCaptured] = {EMPTY, NONE};
    }

    //Promote pawn
    if (move.promotion != EMPTY)
    {
        board[move.toRow][move.toCol] = {move.promotion, old_p.color};
    }

    //set flags
    //enPassant
    enPassantRow = -1;
    enPassantCol = -1;

    //Halfmove clock 
    if (old_p.type == PAWN || captured.type != EMPTY)
        halfMoveClock = 0;
    else    
        halfMoveClock++;

    //castle - king
    if (old_p.type == KING)
    {
        if (old_p.color == WHITE)
        {
            whiteKingsSideCastle = false;
            whiteQueensSideCastle = false;
        }
        else if (old_p.color == BLACK)
        {
            blackKingsSideCastle = false;
            blackQueensSideCastle = false;
        }
    }
    //castle - rook moved
    if (old_p.type == ROOK)
    {
        if (old_p.color == WHITE)
        {
            if (move.fromRow == 7 && move.fromCol == 0)
                whiteQueensSideCastle = false;
            
            if (move.fromRow == 7 && move.fromCol == 7)
                whiteKingsSideCastle = false;
        }
        else
        {
            if (move.fromRow == 0 && move.fromCol == 0)
                blackQueensSideCastle = false;

            if (move.fromRow == 0 && move.fromCol == 7)
                blackKingsSideCastle = false;
        }
    }  
    //castle - rook got captured 
    if (captured.type == ROOK)
    {
        if (captured.color == WHITE)
        {
            if (move.toRow == 7 && move.toCol == 0)
                whiteQueensSideCastle = false;
            
            if (move.toRow == 7 && move.toCol == 7)
                whiteKingsSideCastle = false;
        }
        else if (captured.color == BLACK)
        {
            if (move.toRow == 0 && move.toCol == 0)
                blackQueensSideCastle = false;
            
            if (move.toRow == 0 && move.toCol == 7)
                blackKingsSideCastle = false;
        }
    }

    //en passant
    if (old_p.type == PAWN && abs(move.toRow - move.fromRow) == 2)
    {
        enPassantRow = (move.fromRow + move.toRow) / 2;
        enPassantCol = move.fromCol;
    }
    //pawn promotion
    if (old_p.type == PAWN)
    {
        if ((old_p.color == WHITE && move.toRow == 0) ||
            (old_p.color == BLACK && move.toRow == 7))
        {
            board[move.toRow][move.toCol].type =
                (move.promotion == EMPTY ? QUEEN : move.promotion);
        }
    }
    //set current turn to the opposite color
    currentTurn = currentTurn == WHITE ? BLACK : WHITE;

    return true;
}

bool Board::isSquareAttacked(int row, int col, Color byColor) const
{
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            Piece p = getPiece(r, c);

            if (p.color != byColor || p.type == EMPTY)
                continue;

            const auto& attack_moves = getAttackMoves(*this, r, c);

            for (const Move& m : attack_moves)
            {
                if (m.toRow == row && m.toCol == col)
                    return true;
            }
        }
    }

    return false;
}

bool Board::isInCheck(Color color) const
{
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            Piece p = getPiece(r, c);

            if (p.color != color || p.type != KING)
                continue;
            
            Color byColor = color == WHITE ? BLACK : WHITE;

            return isSquareAttacked(r, c, byColor);
        }
    }

    return false;
}

bool Board::hasAnyLegalMove(Color color) const
{
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            Piece p = getPiece(r, c);

            if (p.color != color)
                continue;

            
            const auto legal_moves = getLegalMoves(*this, r, c);

            for (const auto& move : legal_moves)
            {
                Board temp = *this;

                if (!temp.makeMove(move))
                    continue;
                
                if (!temp.isInCheck(color))
                    return true;
            }
        }
    }

    return false;
}

bool Board::isCheckmate(Color color) const
{
    return isInCheck(color) && !hasAnyLegalMove(color);
}


bool Board::isStalemate(Color color) const
{
    return !isInCheck(color) && !hasAnyLegalMove(color);
}

bool Board::canCastleKingside(Color color) const
{
    return color == WHITE ? whiteKingsSideCastle :
        blackKingsSideCastle;
}

bool Board::canCastleQueenside(Color color) const
{
    return color == WHITE ? whiteQueensSideCastle :
        blackQueensSideCastle;
}

bool Board::hasEnPassant() const
{
    return enPassantRow == -1 ? false : true;
}

std::pair<int, int> Board::getEnPassantSquare() const
{
    return {enPassantRow, enPassantCol};
}

int Board::getHalfMoveClock() const
{
    return halfMoveClock;
}

Color Board::getCurrentTurn() const
{
    return currentTurn;
}
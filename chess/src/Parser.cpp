#include "Parser.h"
#include "Move.h"
#include <iostream>

Parser::Parser(Board& b) : b(b) {};

std::pair<int, int> Parser::parsePosition(const std::string& s) const
{
    if (s.size() != 2)
    {
        return {-1,-1};
    }

    char file = s[0];
    char rank = s[1];

    if (file < 'a' || file > 'h' || rank < '1' || rank > '8')
        return {-1,-1};

    int row = 8 - (rank - '0');
    int col = file - 'a';

    std::cout << "row: " << row << "col: " << col << "\n";

    return {row, col};
}

void Parser::makeMove(const std::string& s) 
{
    if (s.length() != 4)
    {
        std::cout << "invalid move! - s.lenght()\n";
        return;
    }

    std::pair<int, int> old_pos = parsePosition(s.substr(0, 2));
    std::pair<int, int> new_pos = parsePosition(s.substr(2, 2));

    if (old_pos.first == -1 || new_pos.first == -1)
    {
        std::cout << "invalid move!\n";
        return;
    }
    
    Piece p = b.getPiece(old_pos.first, old_pos.second);
    bool is_castle = false;
    bool is_enPassant = false;
    

    if (p.type == KING && abs(new_pos.second - old_pos.second) == 2)
        is_castle = true;
    
    if (p.type == PAWN)
    {
        auto ep = b.getEnPassantSquare();

        if (ep != std::pair<int,int>{-1, -1} &&
            new_pos.first == ep.first &&
            new_pos.second == ep.second &&
            std::abs(new_pos.second - old_pos.second) == 1 &&
            ((p.color == WHITE && new_pos.first == old_pos.first - 1) ||
            (p.color == BLACK && new_pos.first == old_pos.first + 1)))
        {
            is_enPassant = true;
        }
    }
    

    if (is_castle)
    {
        Move m = {old_pos.first, old_pos.second, new_pos.first, new_pos.second, EMPTY, true};
        b.makeMove(m);
    }
    else if (is_enPassant)
    {
        std::cout << "DEBUG: ENPASSANT TRIGGERED\n";
        Move m = {old_pos.first, old_pos.second, new_pos.first, new_pos.second, EMPTY, false, true};
        b.makeMove(m);
    }
    else
    {
        Move m = {old_pos.first, old_pos.second, new_pos.first, new_pos.second};
        b.makeMove(m);
    }
}
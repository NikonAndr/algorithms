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
    
    Move m = {old_pos.first, old_pos.second, new_pos.first, new_pos.second};

    b.makeMove(m);
}
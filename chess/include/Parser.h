#pragma once 
#include "Board.h"


class Parser
{
private:
    Board& b;
public:
    Parser(Board& b);


    std::pair<int, int> parsePosition(const std::string& s) const;
    void makeMove(const std::string& s);
};
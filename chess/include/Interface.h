#pragma once 
#include "Parser.h"

class Interface
{
private:
    Parser parser;
    Board& board;
public:
    Interface(Board& b);

    void show_if();
};
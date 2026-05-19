#pragma once 
#include "Parser.h"

class Interface
{
private:
    Parser parser;
    Board& board;
public:
    bool debug = false;
    Interface(Board& b);

    void show_if();
};
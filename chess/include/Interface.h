#pragma once 
#include "Parser.h"
#include "AI.h"

class Interface
{
private:
    AI AIbot;
    Parser parser;
    Board& board;
public:
    bool debug = false;
    bool against_ai = true;
    Interface(Board& b, AI bot);

    void show_if();
};
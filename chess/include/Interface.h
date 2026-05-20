#pragma once 
#include "Parser.h"
#include "AI.h"

class Interface
{
private:
    AI AIbot;
    AI AIbot2;
    Parser parser;
    Board& board;
public:
    bool debug = false;
    bool against_ai = false;
    bool ai_against_ai = true;
    Interface(Board& b, AI bot, AI bot2);

    void show_if();
};
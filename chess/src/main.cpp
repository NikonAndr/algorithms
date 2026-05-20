#include "Interface.h"
#include "AI.h"
#include <iostream>

int main()
{
    bool castle_test = false;
    bool promotion_test = false;
    bool checkmate_test = false;
    Board b(castle_test, promotion_test, checkmate_test);
    AI bot(BLACK);
    AI bot2(WHITE);
    Interface interface(b, bot, bot2);
    interface.debug = false;

    interface.show_if();
}   
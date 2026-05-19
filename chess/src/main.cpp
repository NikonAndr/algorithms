#include "Interface.h"
#include <iostream>

int main()
{
    bool castle_test = false;
    bool promotion_test = true;
    Board b(castle_test, promotion_test);
    Interface interface(b);
    interface.debug = false;

    interface.show_if();
}   
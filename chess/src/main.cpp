#include "Interface.h"
#include <iostream>

int main()
{
    bool castle_check = true;
    Board b;
    Interface interface(b);
    interface.debug = true;

    interface.show_if();
}   
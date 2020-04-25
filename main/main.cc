#include "game.h"
#include <stdlib.h>
#include <iostream>

int main() {
    // Run game
    Game g;
    if(g.init() != 0) return -1;
    g.run();

    return 0;
}

#include "generation/levelgenerator.h"
#include <stdlib.h>

int main() {
    // Run game
    LevelGenerator l(20, 20);
    l.cpeRoom();
    l.printCharBoard();

    return 0;
}

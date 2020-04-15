#include "game.h"
#include <stdlib.h>

int main() {
    // Turn input echo off
    int err = system("stty -echo");
    if(err == -1) return -1;

    // Run game
    Game g;
    g.init();
    g.run();

    return 0;
}

#include "tools/user_input.h"
#include <iostream>

//TODO: misschien niet last?
int lastKeyPressed() {
    char c;
    int inbuff = _kbhit();
    // If characters were pressed
    if(inbuff != 0) {
        // Get the last one
        for(int i = 0; i < inbuff; i++) {
            std::cin.get(c);
        }
        return c;
    }
    else {
        return -1;
    }
}

Action getAction(int key) {
    switch (key) {
        case 'w': return ACTION_MOVEUP;
        case 's': return ACTION_MOVEDOWN;
        case 'd': return ACTION_MOVERIGHT;
        case 'a': return ACTION_MOVELEFT;
        case ' ': return ACTION_SHOOT;
        default: case -1 : return ACTION_NONE;
    }
}

#include "tools/user_input.h"
#include <iostream>


InputHandler::InputHandler() {}

InputHandler::~InputHandler() {}


void InputHandler::init(WINDOW* w) {
    win = w;
}


void InputHandler::readKeys() {
    keysPressed.clear();

    int key = wgetch(win);
    while(key != ERR) {
        keysPressed.push_back(key);
        key = wgetch(win);
    }
}

Input InputHandler::getInput() {
    readKeys();
    Input tmp;
    tmp.fired = false;
    tmp.act = ACTION_NONE;

    // If space is held, shoot. Use last movement key to determine direction
    for(auto &i : keysPressed) {
        if(i == ' ') tmp.fired = true;
        if(i == 'w') tmp.act = ACTION_MOVEUP;
        if(i == 's') tmp.act = ACTION_MOVEDOWN;
        if(i == 'd') tmp.act = ACTION_MOVERIGHT;
        if(i == 'a') tmp.act = ACTION_MOVELEFT;
        if(i == KEY_BACKSPACE) tmp.act = GAME_PAUSE;
    }

    return tmp;
}


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

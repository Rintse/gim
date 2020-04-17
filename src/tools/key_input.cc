#include "tools/key_input.h"
#include <iostream>
#include <algorithm>

KeyHandler::KeyHandler() {}

KeyHandler::~KeyHandler() {}

void KeyHandler::updateKeys() {
    while(SDL_PollEvent(&events)){
        if(events.type == SDL_KEYDOWN) {
            SDL_Keycode key = events.key.keysym.sym;
            keys[key] = true;
            if(key == SDLK_w || key == SDLK_s || key == SDLK_d || key == SDLK_a) {
                auto it = std::find(movementQ.begin(), movementQ.end(), key);
                if(it == movementQ.end()) {
                    movementQ.push_back(key);
                }
            }
        }
        else if(events.type == SDL_KEYUP) {
            keys[events.key.keysym.sym] = false;
            auto it = std::find(movementQ.begin(), movementQ.end(), events.key.keysym.sym);
            if(it != movementQ.end()) {
                movementQ.erase(it);
            }
        }
    }
}

Input KeyHandler::getInput() {
    updateKeys();

    Input in;
    in.fired = false;
    in.act = ACTION_NONE;

    // Character controls
    if(keys[SDLK_SPACE]) { in.fired = true; }
    // Always use movement key that was pressed down last (and is still pressed)
    if(!movementQ.empty()) {
        if(movementQ.back() == SDLK_w) in.act = ACTION_MOVEUP;
        else if(movementQ.back() == SDLK_s) in.act = ACTION_MOVEDOWN;
        else if(movementQ.back() == SDLK_d) in.act = ACTION_MOVERIGHT;
        else if(movementQ.back() == SDLK_a) in.act = ACTION_MOVELEFT;
    }

    // Game controls
    if(keys[SDLK_ESCAPE]) { in.act = GAME_PAUSE; }

    return in;
}

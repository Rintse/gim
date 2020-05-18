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

            // Make a queue for movement keys so that they override each other
            if(key == SDLK_w || key == SDLK_s || key == SDLK_d || key == SDLK_a) {
                auto it = std::find(movementQ.begin(), movementQ.end(), key);
                if(it == movementQ.end()) {
                    movementQ.push_back(key);
                }
            }
        }
        else if(events.type == SDL_KEYUP) {
            SDL_Keycode key = events.key.keysym.sym;
            // Make sure a pause press gets handled
            if(key != SDLK_ESCAPE && key != SDLK_RETURN) {
                keys[key] = false;
            }
            if(key == SDLK_w || key == SDLK_s || key == SDLK_d || key == SDLK_a) {
                auto it = std::find(movementQ.begin(), movementQ.end(), key);
                if(it != movementQ.end()) {
                    movementQ.erase(it);
                }
            }
        }
    }
}

Input KeyHandler::getInput() {
    updateKeys();

    Input in;
    in.fired = false;
    in.sprint = false;
    in.act = ACTION_NONE;

    // Character controls
    if(keys[SDLK_SPACE]) { in.fired = true; }
    if(keys[SDLK_LSHIFT]) { in.sprint = true; }
    if(keys[SDLK_ESCAPE]) {
        in.act = GAME_PAUSE;
        keys[SDLK_ESCAPE] = false;
        return in;
    }
    if(keys[SDLK_f]) {
      in.act = ACTION_PORTAL;
      return in;
    }

    // Always use movement key that was pressed down last (and is still pressed)
    if(!movementQ.empty()) {
        if(movementQ.back() == SDLK_w) in.act = ACTION_MOVEUP;
        else if(movementQ.back() == SDLK_s) in.act = ACTION_MOVEDOWN;
        else if(movementQ.back() == SDLK_d) in.act = ACTION_MOVERIGHT;
        else if(movementQ.back() == SDLK_a) in.act = ACTION_MOVELEFT;
    }
    else if(keys[SDLK_RETURN]) {
        in.act = GAME_CLOSE;
        keys[SDLK_RETURN] = false;
    }

    return in;
}

#include "tools/key_input.h"
#include <iostream>


KeyHandler::KeyHandler() {}

KeyHandler::~KeyHandler() {}

void KeyHandler::updateKeys() {
    while(SDL_PollEvent(&events)){
        switch( events.type ){
            case SDL_KEYDOWN:
                switch( events.key.keysym.sym ){
                    case SDLK_w: keys.w = true; break;
                    case SDLK_s: keys.s = true; break;
                    case SDLK_d: keys.d = true; break;
                    case SDLK_a: keys.a = true; break;
                    case SDLK_SPACE: keys.space = true; break;
                    case SDLK_ESCAPE: keys.esc = true; break;
                    default: break;
                } break;
            case SDL_KEYUP:
                switch( events.key.keysym.sym ){
                    case SDLK_w: keys.w = false; break;
                    case SDLK_s: keys.s = false; break;
                    case SDLK_d: keys.d = false; break;
                    case SDLK_a: keys.a = false; break;
                    case SDLK_SPACE: keys.space = false; break;
                    case SDLK_ESCAPE: keys.esc = false; break;
                    default: break;
                } break;
            default: break;
        }
    }
}

Input KeyHandler::getInput() {

}

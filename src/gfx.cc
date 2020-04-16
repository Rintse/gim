#include "gfx.h"
#include "game.h"
#include <iostream>

GFX::GFX(Game* g) {
    game = g;
}

GFX::~GFX() {
    SDL_DestroyWindow(window);
    SDL_Quit();

}

void GFX::init() {
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else {
        //Create window
        window = SDL_CreateWindow(  "Notorious George",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    LVL_WIDTH,
                                    LVL_HEIGHT,
                                    SDL_WINDOW_SHOWN    );
        if( window == NULL ) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else { // Get window surface
            surface = SDL_GetWindowSurface( window );
        }
    }
}


void GFX::drawGame() {

}

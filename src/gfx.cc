#include "gfx.h"
#include "game.h"
#include <iostream>

GFX::GFX(Game* g) {
    game = g;
}

GFX::~GFX() {
    for(auto &i : sprites) {
        SDL_FreeSurface(i.second);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void GFX::loadSprites() {
    printf( "Loading sprites\n");
    // Player
    sprites['^'] = SDL_LoadBMP("img/player/up.bmp");
    sprites['>'] = SDL_LoadBMP("img/player/right.bmp");
    sprites['<'] = SDL_LoadBMP("img/player/left.bmp");
    sprites['v'] = SDL_LoadBMP("img/player/down.bmp");
    // Enemy
    sprites['w'] = SDL_LoadBMP("img/enemy/up.bmp");
    sprites['d'] = SDL_LoadBMP("img/enemy/right.bmp");
    sprites['a'] = SDL_LoadBMP("img/enemy/left.bmp");
    sprites['s'] = SDL_LoadBMP("img/enemy/down.bmp");
    // George
    sprites['A'] = SDL_LoadBMP("img/wall.bmp");
    sprites['B'] = SDL_LoadBMP("img/wall.bmp");
    sprites['C'] = SDL_LoadBMP("img/wall.bmp");
    sprites['D'] = SDL_LoadBMP("img/wall.bmp");
    sprites['E'] = SDL_LoadBMP("img/wall.bmp");
    sprites['F'] = SDL_LoadBMP("img/wall.bmp");
    // Other
    sprites['#'] = SDL_LoadBMP("img/wall.bmp");
    sprites[' '] = SDL_LoadBMP("img/empty.bmp");
    sprites['o'] = SDL_LoadBMP("img/projectile.bmp");
    sprites['x'] = SDL_LoadBMP("img/projectile.bmp"); //TODO: bullet image
    sprites['|'] = SDL_LoadBMP("img/projectile.bmp"); //TODO: laser image
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
                                    LVL_WIDTH*SPRITE_DIM,
                                    LVL_HEIGHT*SPRITE_DIM,
                                    SDL_WINDOW_SHOWN    );
        if( window == NULL ) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else { // Get window surface
            surface = SDL_GetWindowSurface( window );
        }
    }

    loadSprites();
}


void GFX::drawGame() {
    SDL_Rect pos;
    pos.w = pos.h = SPRITE_DIM;
    char c;

    for(int j = 0; j < LVL_HEIGHT; j++) {
        for(int i = 0; i < LVL_WIDTH; i++) {
            pos.x = i*SPRITE_DIM;
            pos.y = j*SPRITE_DIM;
            Square* s = game->getLevel()->getSquare(i,j);
            if(s->getPlayer() != 0) {
                c = s->getPlayer()->token();
            }
            else if(s->getEnemy() != 0) {
                c = s->getEnemy()->token();
            }
            else if(s->getProjectile() != 0) {
                c = s->getProjectile()->token();
            }
            else {
                c = s->token();
            }

            SDL_BlitSurface(sprites[c], NULL, surface, &pos);
        }
    }

    SDL_UpdateWindowSurface(window);
}

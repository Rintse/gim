#include "gfx.h"
#include "game.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>

GFX::GFX(Game* g) {
    game = g;
    scale = DEFAULT_SCALE; //TODO: niet hier defined

    // Helper rectangle
    dst.w = dst.h = SPRITE_DIM*scale;
    src.w = src.h = SPRITE_DIM;
    src.x = src.y = 0;
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
    // George heart
    sprites['4'] = SDL_LoadBMP("img/fullheart.bmp");
    sprites['3'] = SDL_LoadBMP("img/75heart.bmp");
    sprites['2'] = SDL_LoadBMP("img/50heart.bmp");
    sprites['1'] = SDL_LoadBMP("img/25heart.bmp");
    // Other
    sprites['H'] = SDL_LoadBMP("img/hp.bmp");
    sprites['L'] = SDL_LoadBMP("img/heart.bmp");
    sprites['#'] = SDL_LoadBMP("img/wall.bmp");
    sprites[' '] = SDL_LoadBMP("img/empty.bmp");
    sprites['o'] = SDL_LoadBMP("img/projectile.bmp");
    sprites['x'] = SDL_LoadBMP("img/bullet.bmp");
    sprites['/'] = SDL_LoadBMP("img/laserleft.bmp");
    sprites['|'] = SDL_LoadBMP("img/laserright.bmp");
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
                                    2*LVL_WIDTH*SPRITE_DIM,
                                    2*LVL_HEIGHT*SPRITE_DIM,
                                    SDL_WINDOW_SHOWN    );
        if( window == NULL ) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else { // Get window surface
            surface = SDL_GetWindowSurface( window );
        }
    }

    loadSprites();
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("img/Amatic-Bold.ttf", 48);
    SDL_Color foregroundColor = { 255, 255, 255 };
    SDL_Color backgroundColor = { 0, 0, 255 };
    pauseText = TTF_RenderText_Shaded(font,
        "PAUSED\n\nPress enter to quit\nPress esc to continue",
        foregroundColor,
        backgroundColor
    );
    pauseX = (2*LVL_WIDTH*SPRITE_DIM - pauseText->w) / 2;
    pauseY = (2*LVL_HEIGHT*SPRITE_DIM - pauseText->h) / 2;
}


void GFX::drawHeader() {
    char c;

    if(game->getLevel()->getGeorge() != 0) {
        int full = game->getLevel()->getGeorge()->getHP() / 4;
        int quart = game->getLevel()->getGeorge()->getHP() % 4;
        dst.y = 0;
        for(int i = 0; i < LVL_WIDTH; i++) {
            dst.x = scale*i*SPRITE_DIM;
            if(i < full) c = '4';
            else if( i == full && quart != 0) c = quart + 48;
            else c = game->getLevel()->getSquare(i,(LVL_HEIGHT-1))->token();
            SDL_BlitScaled(sprites[c], &src, surface, &dst);
        }
    }
    else {
        for(int i = 0; i < LVL_WIDTH; i++) {
            dst.x = scale*i*SPRITE_DIM;
            c = game->getLevel()->getSquare(i,(LVL_HEIGHT-1))->token();
            SDL_BlitScaled(sprites[c], &src, surface, &dst);
        }
    }
}

void GFX::drawFooter() {
    char c = 'H';

    int hp = game->getLevel()->getPlayer()->getHP();
    dst.y = scale*(LVL_HEIGHT-1)*SPRITE_DIM;
    for(int i = 0; i < LVL_WIDTH; i++) {
        dst.x = scale*i*SPRITE_DIM;
        if(i >= hp) c = game->getLevel()->getSquare(i,(LVL_HEIGHT-1))->token();
        SDL_BlitScaled(sprites[c], &src, surface, &dst);
    }
}


void GFX::drawPauseMenu() {
    std::cout << "drawing pause menu" << std::endl;
    SDL_Rect pos, surfdims;
    pos.x = pauseX;
    pos.y = pauseY;
    surfdims.x = 0;
    surfdims.y = 0;
    pos.w = surfdims.w = pauseText->w;
    pos.h = surfdims.h = pauseText->h;

    SDL_BlitSurface(pauseText, &surfdims, surface, &pos);

}


void GFX::drawGame() {
    char c;

    for(int j = 0; j < LVL_HEIGHT; j++) {
        for(int i = 0; i < LVL_WIDTH; i++) {
            dst.x = scale*i*SPRITE_DIM;
            dst.y = scale*j*SPRITE_DIM;
            c = game->getLevel()->getSquare(i,j)->token();
            SDL_BlitScaled(sprites[c], &src, surface, &dst);
        }
    }

    drawHeader();
    drawFooter();


    SDL_UpdateWindowSurface(window);
}

#include "gfx/gfx.h"
#include "game.h"
#include <iostream>
#include <X11/Xlib.h>
#include "tools/distance.h"
#include "gfx/spritemap.h"

GFX::GFX(Game* g) {
    game = g;
    scale = DEFAULT_SCALE;
}

GFX::~GFX() {
    for(auto &i : sprites) {
        SDL_FreeSurface(i.second);
    }
    delete startMenu;
    delete pauseMenu;
    delete wonMenu;
    delete lostMenu;
    SDL_FreeSurface(black);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int GFX::checkScreenSize() {
    int err = 0;
    Display* d = XOpenDisplay(NULL);
    Screen*  s = DefaultScreenOfDisplay(d);
    if(s->height < LVL_HEIGHT*SPRITE_DIM || s->width < LVL_WIDTH*SPRITE_DIM) {
        std::cout << "Screen resolution not supported" << std::endl;
        std::cout << "Current: " << s->width << "x" << s->height << std::endl;
        std::cout << "Minimum: " << LVL_WIDTH*SPRITE_DIM
        << "x" << LVL_HEIGHT*SPRITE_DIM << "." << std::endl;
        err = -1;
    }

    int xscale = s->width / (LVL_WIDTH*SPRITE_DIM);
    int yscale = s->height / (LVL_HEIGHT*SPRITE_DIM);
    scale = xscale < yscale ? xscale : yscale;
    height = scale*LVL_HEIGHT*SPRITE_DIM;
    width = scale*LVL_WIDTH*SPRITE_DIM;
    // Helper rectangle
    dst.w = dst.h = SPRITE_DIM*scale;
    src.w = src.h = SPRITE_DIM;
    src.x = src.y = 0;
    return err;
}

int GFX::init() {
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else {
        window = SDL_CreateWindow(  "Notorious George",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    width, height,
                                    SDL_WINDOW_SHOWN    );
        if( window == NULL ) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else { // Get window surface
            surface = SDL_GetWindowSurface( window );
        }
    }

    sprites = getSpriteMap();

    // Black squares for FOW
    black =  SDL_CreateRGBSurface(0,SPRITE_DIM*scale,SPRITE_DIM*scale,32,0,0,0,0);
    SDL_FillRect(black, NULL, SDL_MapRGB(black->format, 0, 0, 0));

    // The various menus
    TTF_Init();
    startMenu = new Menu({
        " The Notorious G.E.O.R.G.E ",
        " Controls: ",
        " Move: WASD (shift to sprint)",
        " Shoot: Space ",
        " Place home portal: f ",
        " Press return to start "
        },
        {3, 2, 1, 1, 1, 2},
        scale*LVL_WIDTH*SPRITE_DIM,
        scale*LVL_HEIGHT*SPRITE_DIM
    );

    pauseMenu = new Menu({
        " PAUSED ",
        " Continue: ESC ",
        " Exit: Return"
        },
        {3, 2, 2},
        scale*LVL_WIDTH*SPRITE_DIM,
        scale*LVL_HEIGHT*SPRITE_DIM
    );

    wonMenu = new Menu({
        " Congratulations! ",
        " You defeated G.E.O.R.G.E ",
        " Press return to close the game "
        },
        {3, 2, 1},
        scale*LVL_WIDTH*SPRITE_DIM,
        scale*LVL_HEIGHT*SPRITE_DIM
    );

    lostMenu = new Menu({
        " YOU DIED ",
        " Press return to close the game "
        },
        {3, 2},
        scale*LVL_WIDTH*SPRITE_DIM,
        scale*LVL_HEIGHT*SPRITE_DIM
    );

    return 0;
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
            else c = game->getLevel()->getSquare(i,0)->token();
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
    char c = '?';

    int hp = game->getLevel()->getPlayer()->getHP();
    dst.y = scale*(LVL_HEIGHT-1)*SPRITE_DIM;
    for(int i = 0; i < LVL_WIDTH-1; i++) {
        dst.x = scale*i*SPRITE_DIM;
        if(i >= hp) c = game->getLevel()->getSquare(i,(LVL_HEIGHT-1))->token();
        SDL_BlitScaled(sprites[c], &src, surface, &dst);
    }

    dst.x = scale*(LVL_WIDTH-1)*SPRITE_DIM;
    if(game->getLevel()->getPlayer()->getPortal()) {
      c = 'p';
    }
    else {
      c = game->getLevel()->getSquare(LVL_WIDTH-1,(LVL_HEIGHT-1))->token();
    }
    SDL_BlitScaled(sprites[c], &src, surface, &dst);
}

void GFX::drawPauseMenu() {
    drawMenu(pauseMenu);
}
void GFX::drawEndMenu(bool won) {
    if(won) drawMenu(wonMenu);
    else drawMenu(lostMenu);
}
void GFX::drawStartMenu() {
    drawMenu(startMenu);
}


void GFX::drawMenu(Menu* menu) {
    SDL_Rect pos, surfdims;

    pos.y = menu->Y;
    surfdims.x = surfdims.y = 0;
    for(unsigned i = 0; i < menu->surfs.size(); i++) {
        pos.x = menu->Xs[i];
        pos.w = surfdims.w = menu->surfs[i]->w;
        pos.h = surfdims.h = menu->surfs[i]->h;
        SDL_BlitSurface(menu->surfs[i], &surfdims, surface, &pos);
        pos.y += menu->surfs[i]->h;
    }

    SDL_UpdateWindowSurface(window);
}

void GFX::drawGame() {
    Square* ps = game->getLevel()->getPlayer()->getSquare();
    int viewDistance = game->getLevel()->getViewDistance();
    // std::cout << "viewDistance: " << viewDistance << std::endl;

    for(int j = 0; j < LVL_HEIGHT; j++) {
        for(int i = 0; i < LVL_WIDTH; i++) {
            dst.x = scale*i*SPRITE_DIM;
            dst.y = scale*j*SPRITE_DIM;
            Square* s = game->getLevel()->getSquare(i,j);
            if(dist(ps, s) > viewDistance) {
                SDL_BlitScaled(black, &src, surface, &dst);
            }
            else {
                SDL_BlitScaled(sprites[s->token()], &src, surface, &dst);
            }
        }
    }

    drawHeader();
    drawFooter();

    SDL_UpdateWindowSurface(window);
}

#include "gfx.h"
#include "game.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <X11/Xlib.h>
#include "tools/distance.h"

GFX::GFX(Game* g) {
    game = g;
    scale = DEFAULT_SCALE;
}

GFX::~GFX() {
    for(auto &i : sprites) {
        SDL_FreeSurface(i.second);
    }
    delete black;
    delete[] pauseX;
    delete[] pauseText;
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void GFX::loadSprites() {
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
    sprites['A'] = SDL_LoadBMP("img/george/a.bmp");
    sprites['B'] = SDL_LoadBMP("img/george/b.bmp");
    sprites['C'] = SDL_LoadBMP("img/george/c.bmp");
    sprites['D'] = SDL_LoadBMP("img/george/d.bmp");
    sprites['E'] = SDL_LoadBMP("img/george/e.bmp");
    sprites['F'] = SDL_LoadBMP("img/george/f.bmp");
    sprites['G'] = SDL_LoadBMP("img/george/g.bmp");
    sprites['H'] = SDL_LoadBMP("img/george/h.bmp");
    sprites['I'] = SDL_LoadBMP("img/george/i.bmp");
    sprites['J'] = SDL_LoadBMP("img/george/j.bmp");
    sprites['K'] = SDL_LoadBMP("img/george/k.bmp");
    sprites['L'] = SDL_LoadBMP("img/george/l.bmp");
    sprites['M'] = SDL_LoadBMP("img/george/m.bmp");
    sprites['N'] = SDL_LoadBMP("img/george/n.bmp");
    sprites['O'] = SDL_LoadBMP("img/george/o.bmp");
    sprites['P'] = SDL_LoadBMP("img/george/p.bmp");
    sprites['Q'] = SDL_LoadBMP("img/george/q.bmp");
    sprites['R'] = SDL_LoadBMP("img/george/r.bmp");
    sprites['S'] = SDL_LoadBMP("img/george/s.bmp");
    sprites['T'] = SDL_LoadBMP("img/george/t.bmp");
    sprites['U'] = SDL_LoadBMP("img/george/u.bmp");
    // George heart
    sprites['4'] = SDL_LoadBMP("img/fullheart.bmp");
    sprites['3'] = SDL_LoadBMP("img/75heart.bmp");
    sprites['2'] = SDL_LoadBMP("img/50heart.bmp");
    sprites['1'] = SDL_LoadBMP("img/25heart.bmp");
    // Other
    sprites['?'] = SDL_LoadBMP("img/hp.bmp");
    sprites['h'] = SDL_LoadBMP("img/heart.bmp");
    sprites['f'] = SDL_LoadBMP("img/powerup.bmp");
    sprites['#'] = SDL_LoadBMP("img/wall.bmp");
    sprites[' '] = SDL_LoadBMP("img/empty.bmp");
    sprites['o'] = SDL_LoadBMP("img/projectile.bmp");
    sprites['x'] = SDL_LoadBMP("img/bullet.bmp");
    sprites['/'] = SDL_LoadBMP("img/laserleft.bmp");
    sprites['|'] = SDL_LoadBMP("img/laserright.bmp");
}


void GFX::initPauseMenu() {
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("img/Amatic-Bold.ttf", 48);
    SDL_Color backgroundColor = { 97, 60, 120 };
    SDL_Color foregroundColor = { 42, 44, 44 };
    pauseText = new SDL_Surface*[3];
    pauseX = new int[3];
    pauseText[0] = TTF_RenderText_Shaded(
        font, " PAUSED ", foregroundColor, backgroundColor
    );
    pauseText[1] = TTF_RenderText_Shaded(
        font, " Press esc to continue ", foregroundColor, backgroundColor
    );
    pauseText[2] = TTF_RenderText_Shaded(
        font, " Press enter to quit ", foregroundColor, backgroundColor
    );
    int totalheight = pauseText[0]->h + pauseText[1]->h + pauseText[2]->h;
    pauseY = (scale*LVL_HEIGHT*SPRITE_DIM - totalheight) / 2;
    for(int i = 0; i < 3; i++)
        pauseX[i] = (scale*LVL_WIDTH*SPRITE_DIM - pauseText[i]->w) / 2;
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

    loadSprites();
    initPauseMenu();
    black =  SDL_CreateRGBSurface(0,SPRITE_DIM*scale,SPRITE_DIM*scale,32,0,0,0,0);
    SDL_FillRect(black, NULL, SDL_MapRGB(black->format, 0, 0, 0));

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
    char c = '?';

    int hp = game->getLevel()->getPlayer()->getHP();
    dst.y = scale*(LVL_HEIGHT-1)*SPRITE_DIM;
    for(int i = 0; i < LVL_WIDTH; i++) {
        dst.x = scale*i*SPRITE_DIM;
        if(i >= hp) c = game->getLevel()->getSquare(i,(LVL_HEIGHT-1))->token();
        SDL_BlitScaled(sprites[c], &src, surface, &dst);
    }
}


void GFX::drawPauseMenu() {
    SDL_Rect pos, surfdims;

    pos.y = pauseY;
    surfdims.x = surfdims.y = 0;
    for(int i = 0; i < 3; i++) {
        pos.x = pauseX[i];
        pos.w = surfdims.w = pauseText[i]->w;
        pos.h = surfdims.h = pauseText[i]->h;
        SDL_BlitSurface(pauseText[i], &surfdims, surface, &pos);
        pos.y += pauseText[i]->h;
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

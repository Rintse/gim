#ifndef screen_h
#define screen_h

#include <SDL2/SDL.h>
#include <map>
#include <vector>
#include "gfx/menu.h"

#define DEFAULT_SCALE 1

class Game;

class GFX {
    public:
        GFX(Game* g);
        ~GFX();
        void drawGame();
        void loadSprites();
        int checkScreenSize();
        int init();
        void drawFooter();
        void drawHeader();
        void drawMenu(Menu* menu);
        void drawPauseMenu();
        void drawEndMenu(bool won);
        void drawStartMenu();

    private:
        SDL_Rect src, dst;
        int height, width;
        int scale;
        int* pauseX, *startX, *endX;
        int pauseY, startY, endY;
        Game* game;
        SDL_Surface* surface;
        Menu *startMenu, *pauseMenu, *wonMenu, *lostMenu;
        std::map<char, SDL_Surface*> sprites;
        SDL_Surface* black;
        SDL_Window* window;
};

#endif

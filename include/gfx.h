#ifndef screen_h
#define screen_h

#include <SDL2/SDL.h>
#include <map>
#include <vector>

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
        void initPauseMenu();
        void drawFooter();
        void drawHeader();
        void drawPauseMenu();
    private:
        SDL_Rect src, dst;
        int height, width;
        int scale;
        int* pauseX;
        int pauseY;
        Game* game;
        SDL_Surface* surface;
        SDL_Surface** pauseText;
        std::map<char, SDL_Surface*> sprites;
        SDL_Surface* black;
        SDL_Window* window;
};

#endif

#ifndef screen_h
#define screen_h

#include <SDL2/SDL.h>

class Game;

class GFX {
    public:
        GFX(Game* g);
        ~GFX();
        void drawGame();
        void init();
    private:
        Game* game;
        SDL_Surface* surface;
        SDL_Window* window;
};

#endif

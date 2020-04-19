#ifndef screen_h
#define screen_h

#include <SDL2/SDL.h>
#include <map>
#include <vector>

class Game;

class GFX {
    public:
        GFX(Game* g);
        ~GFX();
        void drawGame();
        void loadSprites();
        void init();
    private:
        Game* game;
        SDL_Surface* surface;
        std::map<char, SDL_Surface*> sprites;
        SDL_Window* window;
};

#endif

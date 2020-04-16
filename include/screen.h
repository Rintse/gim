#ifndef screen_h
#define screen_h

#include <ncurses.h>

class Game;

class Screen {
    public:
        Screen(Game* g);
        ~Screen();
        void drawGame();
        WINDOW* init();
    private:
        Game* game;
        WINDOW* win;
        WINDOW *menu;
};

#endif

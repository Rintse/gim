#ifndef key_input_h
#define key_input_h

#include <SDL2/SDL.h>
#include "tools/actions.h"

struct Input {
    Action act;
    bool fired;
};

struct Keys {
    bool w;
    bool s;
    bool d;
    bool a;
    bool space;
    bool esc;
};

class KeyHandler {
    public:
        KeyHandler();
        ~KeyHandler();
        void updateKeys();
        Input getInput();
    private:
        Keys keys;
        SDL_Event events;
};

#endif

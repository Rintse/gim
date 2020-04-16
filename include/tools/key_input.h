#ifndef key_input_h
#define key_input_h

#include <SDL2/SDL.h>
#include "tools/actions.h"

struct Input {
    Action act;
    bool fired;
};

struct Keys {
    bool w = false;
    bool s = false;
    bool d = false;
    bool a = false;
    bool space = false;
    bool esc = false;
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

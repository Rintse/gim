#ifndef key_input_h
#define key_input_h

#include <SDL2/SDL.h>
#include "tools/actions.h"
#include <map>
#include <list>

struct Input {
    Action act;
    bool fired;
};

class KeyHandler {
    public:
        KeyHandler();
        ~KeyHandler();
        void updateKeys();
        Input getInput();

    private:
        std::map<SDL_Keycode, bool> keys;
        std::list<SDL_Keycode> movementQ;
        SDL_Event events;
};

#endif

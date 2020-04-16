#ifndef user_input_h
#define user_input_h

#include "tools/actions.h"
#include "tools/kbhit.h"
#include <vector>
#include <ncurses.h>

struct Input {
    Action act;
    bool fired;
};

class InputHandler {
    public:
        InputHandler();
        ~InputHandler();
        void init(WINDOW* w);
        void readKeys(); // Reads actual keyboard keys
        Input getInput(); // Determines actions by keys pressed


    private:
        WINDOW* win;
        std::vector<int> keysPressed;
};

//TODO: misschien niet last?
int lastKeyPressed();
Action getAction(int key);

#endif

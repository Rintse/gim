#ifndef actions_h
#define actions_h

#include <string>

enum Action {
    ACTION_MOVEUP,
    ACTION_MOVELEFT,
    ACTION_MOVEDOWN,
    ACTION_MOVERIGHT,
    ACTION_NONE,
    ACTION_SHOOT,
    GAME_CLOSE,
    GAME_PAUSE
};

std::string act_tostr(Action);

#endif

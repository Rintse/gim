#include "tools/actions.h"

std::string act_tostr(Action a) {
    switch (a) {
        case ACTION_MOVEUP: return "moveup"; break;
        case ACTION_MOVELEFT: return "moveleft"; break;
        case ACTION_MOVEDOWN: return "movedown"; break;
        case ACTION_MOVERIGHT: return "moveright"; break;
        case ACTION_NONE: return "none"; break;
        case ACTION_SHOOT: return "shoot"; break;
        case GAME_CLOSE: return "close"; break;
        case GAME_PAUSE: return "pause"; break;
        default: return "not defined";
    }
}

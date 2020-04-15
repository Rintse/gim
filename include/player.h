#ifndef player_h
#define player_h

#include "directions.h"
#include "actions.h"

class Level;
class Square;

class Player {
public:
    Player();
    Player(Level* l);
    void act(Action a);
    void move(Direction dir);
private:
    Level* curLvl;
    Square* curSquare;
    Direction facing;
};

#endif

#ifndef player_h
#define player_h

#include "tools/directions.h"
#include "tools/actions.h"

class Level;
class Square;

class Player {
public:
    Player();
    Player(Level* l);
    void act(Action a);
    void move(Direction dir);
    void shoot();
    void setSquare(Square* s);
    void setLevel(Level* l);
    char token();
    Square* getSquare();

private:
    Level* curLvl;
    Square* curSquare;
    Direction facing;
};

#endif

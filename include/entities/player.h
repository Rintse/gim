#ifndef player_h
#define player_h

#include "tools/directions.h"
#include "tools/actions.h"

#define SLOW_LO_FRAMES 1
#define FAST_LO_FRAMES 0

class Level;
class EmptySquare;
struct Input;

class Player {
public:
    Player();
    Player(Level* l);
    void act(Input a);
    void move(Direction dir);
    void shoot();
    void setSquare(EmptySquare* s);
    void setLevel(Level* l);
    char token();
    EmptySquare* getSquare();
    void takeDamage();
    void pickupHeart();
    int getHP();

private:
    int health;
    Level* curLvl;
    EmptySquare* curSquare;
    Direction facing;
    int lockout;
    int curLOFrames;
};

#endif

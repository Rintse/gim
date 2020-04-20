#ifndef player_h
#define player_h

#include "tools/directions.h"
#include "tools/actions.h"

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
};

#endif

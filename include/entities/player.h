#ifndef player_h
#define player_h

#include "tools/directions.h"
#include "tools/actions.h"

#define SLOW_MLO 1
#define FAST_MLO 0
#define START_SLO 25

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
    void decreaseSLO();
    void setLevel(Level* l);
    char token();
    void advanceLockouts();
    EmptySquare* getSquare();
    void takeDamage();
    void increaseHP();
    int getHP();
    bool getPortal();

private:
    void toStart();

    int health;
    Level* curLvl;
    EmptySquare* curSquare;
    Direction facing;
    int moveLockout, shootLockout;
    int curMLO, curSLO;
    bool portal;
};

#endif

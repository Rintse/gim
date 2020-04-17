#ifndef player_h
#define player_h

#include "tools/directions.h"
#include "tools/actions.h"

class Level;
class Square;
struct Input;

class Player {
public:
    Player();
    Player(Level* l);
    void act(Input a);
    void move(Direction dir);
    void shoot();
    void setSquare(Square* s);
    void setLevel(Level* l);
    char token();
    Square* getSquare();
    void takeDamage();

private:
    int health;
    Level* curLvl;
    Square* curSquare;
    Direction facing;
};

#endif

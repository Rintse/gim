#ifndef george_h
#define george_h

#include "game.h"
#include "georgeparts.h"

#define COOLDOWN_SECONDS 1
#define ROUND_SECONDS 20
#define COOLDOWN_FRAMES (FPS*COOLDOWN_SECONDS)
#define ROUND_FRAMES (FPS*ROUND_SECONDS)

class Level;
class Square;

class George {
public:
    George();
    George(Level* l, Square* s);

    void act();

private:
    Square* curSquare;
    Level* lvl;
    int curRound;
    int frame;

    // zijn voorlopig pointers, moet nog even overnadenken of dat de beste opslag
    // methode is voor elk george deel
    GeorgeA* a;
    GeorgeB* b;
    GeorgeC* c;
    GeorgeD* d;
    GeorgeE* e;
    GeorgeF* f; 

    void attackBullets();
    void attackLasers();
    void attackTinyGeorges();
};

#endif

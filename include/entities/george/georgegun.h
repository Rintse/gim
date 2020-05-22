#ifndef georgegun_h
#define georgegun_h

#include "georgepart.h"
#include "entities/projectiles/georgebullet.h"
#include "entities/projectiles/georgelaser.h"
#include "round.h"

class Level;
class Square;

class GeorgeGun : public GeorgePart {
public:
    GeorgeGun();
    GeorgeGun(Level* l, EmptySquare* s, char t);
    ~GeorgeGun() {};

    void act(Input i);
    void setRound(Round round);

protected:
    Round curRound;
    Direction dir;

    void shootBullet();
    void shootLaser();
};

#endif

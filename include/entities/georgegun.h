#ifndef georgegun_h
#define georgegun_h

#include "georgepart.h"
#include "georgebullet.h"
#include "georgelaser.h"

class Level;
class Square;

class GeorgeGun : public GeorgePart {
public:
    GeorgeGun();
    GeorgeGun(Level* l, Square* s);

    void act(int curRound, Direction dir);
    virtual char token() = 0;

protected:
    void shootBullet();
    void shootLaser();
};

#endif

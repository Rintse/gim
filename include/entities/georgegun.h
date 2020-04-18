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

    void act(Action action);

protected:
    int curRound;
    void shootBullet();
    void shootLaser();
    void setRound(int r);
};

#endif

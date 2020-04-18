#ifndef georgenogun_h
#define georgenogun_h

#include "georgepart.h"

class Level;
class Square;

class GeorgeNoGun : public GeorgePart {
public:
    GeorgeNoGun();
    GeorgeNoGun(Level* l, Square* s);

    void act(Action action);
};

#endif

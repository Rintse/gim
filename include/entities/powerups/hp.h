#ifndef hp_h
#define hp_h

#include "entities/powerups/powerup.h"

class Hp : public Powerup {
    public:
        Hp();
        char token();
        void get(Player* p);
};

#endif

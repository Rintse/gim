#ifndef hp_h
#define hp_h

#include "entities/powerups/powerup.h"

class FasterBullets : public Powerup {
    public:
        FasterBullets();
        char token();
        void get(Player* p);
};

#endif

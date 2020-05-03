#ifndef fb_h
#define fb_h

#include "entities/powerups/powerup.h"

class FasterBullets : public Powerup {
    public:
        FasterBullets();
        char token();
        void get(Player* p);
};

#endif

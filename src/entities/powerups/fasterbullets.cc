#include "entities/powerups/fasterbullets.h"
#include "entities/player.h"

FasterBullets::FasterBullets() {}

char FasterBullets::token() {
    return 'f';
}

void FasterBullets::get(Player* p) {
    p->decreaseSLO();
}

#include "entities/powerups/hp.h"
#include "entities/player.h"

Hp::Hp() {}

char Hp::token() {
    return 'h';
}

void Hp::get(Player* p) {
    p->increaseHP();
}

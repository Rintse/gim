#include "tools/fastrandom.h"
//Marsaglia's xorshf generator, very few operations

FastRandom::FastRandom(){ // Seeding
    x=123456789;
    y=362436069;
    z=521288629;
}

unsigned long FastRandom::getLong(void) { //period 2^96-1
    unsigned long t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;
    t = x;
    x = y;
    y = z;
    z = t ^ x ^ y;
    return z;
}

#include "tools/fastrandom.h"
#include <iostream>
//Marsaglia's xorshf generator, very few operations

FastRandom::FastRandom(){ // TODO, set Seeding
    x=123456789;
    y=362436069;
    z=521288629;
}

double FastRandom::getDouble() {
    return (double)getLong()/(double)0xFFFFFFFFFFFFFFFF;
}

uint64_t FastRandom::getLong() { //period 2^96-1
    uint64_t t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;
    t = x;
    x = y;
    y = z;
    z = t ^ x ^ y;
    return z;
}

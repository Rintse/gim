#ifndef fastrandom_h
#define fastrandom_h

#include <climits>
#include <cstdint>

class FastRandom {
public:
    FastRandom();
    FastRandom(uint64_t seed);
    double getDouble();
    uint64_t getLong();
private:
    uint64_t x,y,z;
};

#endif

#ifndef fastrandom_h
#define fastrandom_h

#include <climits>

class FastRandom {
public:
    FastRandom();
    unsigned long getLong();
    unsigned long getMax();
private:
    int x,y,z;
};

#endif

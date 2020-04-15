#ifndef fastrandom_h
#define fastrandom_h

class FastRandom {
public:
    FastRandom();
    unsigned long getLong();
private:
    int x,y,z;
};

#endif

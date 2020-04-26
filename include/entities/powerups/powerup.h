#ifndef powerup_h
#define powerup_h

class Player;

class Powerup {
    public:
        Powerup();
        virtual ~Powerup();
        virtual void get(Player* p) = 0;
        virtual char token() = 0;
};

#endif

#ifndef dijkstra_h
#define dijkstra_h

class Dijkstra {
    public:
        Dijkstra();
        ~Dijkstra();
    private:
        Level* lvl;
        std::set<Square*> fringe;
}

#endif

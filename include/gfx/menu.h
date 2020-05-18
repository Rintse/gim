#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Menu {
    public:
        Menu(std::vector<std::string> texts, std::vector<int> sizes, int w, int h);
        ~Menu();
        std::vector<SDL_Surface*> surfs;
        int* Xs;
        int Y;
};

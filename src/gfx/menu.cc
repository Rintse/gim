#include "gfx/menu.h"
#include <map>

Menu::Menu(std::vector<std::string> texts, std::vector<int> sizes, int w, int h) {
    // The colours
    SDL_Color fgCol = { 0, 0, 0 };
    SDL_Color bgCol = { 97, 60, 120 };

    // Allocate the fonts
    std::map<int, TTF_Font*> fonts;
    fonts[3] = TTF_OpenFont("img/Amatic-Bold.ttf", 64);
    fonts[2] = TTF_OpenFont("img/Amatic-Bold.ttf", 48);
    fonts[1] = TTF_OpenFont("img/Amatic-Bold.ttf", 32);

    for(unsigned i = 0; i < texts.size(); i++) {
        SDL_Surface* tmp = TTF_RenderText_Shaded(
            fonts[sizes[i]],
            texts[i].c_str(),
            bgCol,
            fgCol
        );
        surfs.push_back(tmp);
    }

    // The positions of the texts
    Xs = new int[texts.size()];
    int totalheight = 0;
    for(unsigned i = 0; i < texts.size(); i++) {
        Xs[i] = (w - surfs[i]->w) / 2;
        totalheight += surfs[i]->h;
    }
    Y = (h - totalheight) / 2;
}

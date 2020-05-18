#include "gfx/spritemap.h"

std::map<char, SDL_Surface*> getSpriteMap() {
    std::map<char, SDL_Surface*> sprites;
    // Player
    sprites['^'] = SDL_LoadBMP("img/player/up.bmp");
    sprites['>'] = SDL_LoadBMP("img/player/right.bmp");
    sprites['<'] = SDL_LoadBMP("img/player/left.bmp");
    sprites['v'] = SDL_LoadBMP("img/player/down.bmp");
    // Enemy
    sprites['w'] = SDL_LoadBMP("img/enemy/up.bmp");
    sprites['d'] = SDL_LoadBMP("img/enemy/right.bmp");
    sprites['a'] = SDL_LoadBMP("img/enemy/left.bmp");
    sprites['s'] = SDL_LoadBMP("img/enemy/down.bmp");
    // George
    sprites['A'] = SDL_LoadBMP("img/george/a.bmp");
    sprites['B'] = SDL_LoadBMP("img/george/b.bmp");
    sprites['C'] = SDL_LoadBMP("img/george/c.bmp");
    sprites['D'] = SDL_LoadBMP("img/george/d.bmp");
    sprites['E'] = SDL_LoadBMP("img/george/e.bmp");
    sprites['F'] = SDL_LoadBMP("img/george/f.bmp");
    sprites['G'] = SDL_LoadBMP("img/george/g.bmp");
    sprites['H'] = SDL_LoadBMP("img/george/h.bmp");
    sprites['I'] = SDL_LoadBMP("img/george/i.bmp");
    sprites['J'] = SDL_LoadBMP("img/george/j.bmp");
    sprites['K'] = SDL_LoadBMP("img/george/k.bmp");
    sprites['L'] = SDL_LoadBMP("img/george/l.bmp");
    sprites['M'] = SDL_LoadBMP("img/george/m.bmp");
    sprites['N'] = SDL_LoadBMP("img/george/n.bmp");
    sprites['O'] = SDL_LoadBMP("img/george/o.bmp");
    sprites['P'] = SDL_LoadBMP("img/george/p.bmp");
    sprites['Q'] = SDL_LoadBMP("img/george/q.bmp");
    sprites['R'] = SDL_LoadBMP("img/george/r.bmp");
    sprites['S'] = SDL_LoadBMP("img/george/s.bmp");
    sprites['T'] = SDL_LoadBMP("img/george/t.bmp");
    sprites['U'] = SDL_LoadBMP("img/george/u.bmp");
    // George heart
    sprites['4'] = SDL_LoadBMP("img/fullheart.bmp");
    sprites['3'] = SDL_LoadBMP("img/75heart.bmp");
    sprites['2'] = SDL_LoadBMP("img/50heart.bmp");
    sprites['1'] = SDL_LoadBMP("img/25heart.bmp");
    // Other
    sprites['?'] = SDL_LoadBMP("img/hp.bmp");
    sprites['h'] = SDL_LoadBMP("img/heart.bmp");
    sprites['f'] = SDL_LoadBMP("img/powerup.bmp");
    sprites['#'] = SDL_LoadBMP("img/wall.bmp");
    sprites[' '] = SDL_LoadBMP("img/empty.bmp");
    sprites['o'] = SDL_LoadBMP("img/projectile.bmp");
    sprites['x'] = SDL_LoadBMP("img/bullet.bmp");
    sprites['/'] = SDL_LoadBMP("img/laserleft.bmp");
    sprites['|'] = SDL_LoadBMP("img/laserright.bmp");

    return sprites;
}

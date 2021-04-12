#ifndef INCLUDE_SPRITE_H
#define INCLUDE_SPRITE_H

#include <SDL.h>
#include <string>
#include "graphics.h"

class Sprite {
public:
    Sprite(Graphics &graphics, int x, int y);
    Sprite(Graphics &graphics, const std::string &file, int srcx, int srcy, int w, int h, int posx, int posy);

    void cleanup();
    virtual void update(Uint32 elapsedTime);
    virtual void draw(Graphics &graphics);

protected:
    SDL_Rect srcrect;
    SDL_Texture *image;

    int x, y;
};

#endif //INCLUDE_SPRITE_H

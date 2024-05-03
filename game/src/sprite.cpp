#include <iostream>

#include "sprite.hpp"

Sprite::Sprite(Graphics &graphics, int posx, int posy)
    : x(posx), y(posy) {
    // nothing
}

Sprite::Sprite(Graphics &graphics, const std::string &file, int srcx, int srcy, int w, int h, int posx, int posy)
    : x(posx), y(posy) {
    srcrect.x = srcx;
    srcrect.y = srcy;
    srcrect.w = w;
    srcrect.h = h;

    image = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(file));
    if (image == nullptr) {
        std::cout << "Unable to load image: " << SDL_GetError() << std::endl;
    }
}

void Sprite::draw(Graphics &graphics) {
    SDL_Rect dstrect = {x, y, srcrect.w, srcrect.h};
    graphics.blitSurface(image, &srcrect, &dstrect);
}

void Sprite::cleanup() {
    SDL_DestroyTexture(image);
}

void Sprite::update(Uint32 elapsedTime) {
    // do nothing
}

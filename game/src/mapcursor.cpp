#include "mapcursor.hpp"

MapCursor::MapCursor(Graphics &graphics, const std::string &file, int srcx, int srcy, int w, int h, int posx, int posy)
    : Sprite(graphics, file, srcx, srcy, w, h, posx, posy), currentFrame("") {
    // nothing
}

void MapCursor::setX(int x) {
    this->x = x;
}

void MapCursor::setY(int y) {
    this->y = y;
}

void MapCursor::setDirection(direction::Direction direction) {
    if (direction == direction::UP) {
        currentFrame = "Up";
    } else if (direction == direction::RIGHT) {
        currentFrame = "Right";
    } else if (direction == direction::LEFT) {
        currentFrame = "Left";
    } else if (direction == direction::DOWN) {
        currentFrame = "Down";
    }
}

void MapCursor::draw(Graphics &graphics) {
    if (frames.count(currentFrame) > 0) {
        srcrect = frames[currentFrame];
        SDL_Rect dstrect = {x + 10, y + 10, 20, 20};
        graphics.blitSurface(image, &srcrect, &dstrect);
    }
}

void MapCursor::setupFrames() {
    frames.insert(std::pair<std::string, SDL_Rect>("Right", {0, 0, 10, 10}));
    frames.insert(std::pair<std::string, SDL_Rect>("Up", {10, 0, 10, 10}));
    frames.insert(std::pair<std::string, SDL_Rect>("Left", {20, 0, 10, 10}));
    frames.insert(std::pair<std::string, SDL_Rect>("Down", {30, 0, 10, 10}));

    currentFrame = "Up";
}

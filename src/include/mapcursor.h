#ifndef INCLUDE_MAPCURSOR_H
#define INCLUDE_MAPCURSOR_H

#include "sprite.h"
#include "globals.h"

class MapCursor : public Sprite {
public:
    MapCursor(Graphics &graphics, const std::string &file, int srcx, int srcy, int w, int h, int posx, int posy);

    void setX(int x);
    void setY(int y);
    void setDirection(direction::Direction direction);
    void setupFrames();
    void draw(Graphics &graphics) override;

private:
    std::string currentFrame;
    std::map<std::string, SDL_Rect> frames;
};

#endif //INCLUDE_MAPCURSOR_H

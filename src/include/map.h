#ifndef INCLUDE_MAP_H
#define INCLUDE_MAP_H

#include "globals.h"
#include "level.h"
#include "mapcursor.h"
#include "sprite.h"

class Map : public Sprite {
public:
    Map(Graphics &graphics, Level *level, int posx, int posy);
    void cleanup();
    void draw(Graphics &graphics);
    void update(Uint32 elapsedTime, Graphics &graphics);
    void updatePlayer(int x, int y, direction::Direction direction);
    void getBounds(int &minx, int &maxx, int &miny, int &maxy);

private:
    void clear(SDL_Renderer *renderer);
    void drawBorders(SDL_Renderer *renderer);
    void drawPlayer(SDL_Renderer *renderer);

    int cellSize;
    int numCells;
    int width;
    int height;

    Uint32 timeToUpdate;
    Uint32 timeElapsed;

    Uint32 *pixels;
    SDL_PixelFormat *pixelFormat;

    int playerx, playery;
    direction::Direction playerdirection;

    MapCursor *arrow;
};

#endif //INCLUDE_MAP_H

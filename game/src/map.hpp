#pragma once

#include "globals.hpp"
#include "level.hpp"
#include "mapcursor.hpp"
#include "player.hpp"
#include "sprite.hpp"

class Map : public Sprite {
   public:
    Map(Graphics& graphics, Level* level, int posx, int posy);
    void cleanup();
    void draw(Graphics& graphics);
    void update(Uint32 elapsedTime, Graphics& graphics, Level* level,
                Player* player);

   private:
    void clear(SDL_Renderer* renderer);
    void drawBorders(SDL_Renderer* renderer);
    void drawPlayer(SDL_Renderer* renderer, Player* player);
    void drawWalls(SDL_Renderer* renderer, Level* level);

    int cellSize;
    int width;
    int height;

    int texWidth;
    int texHeight;

    Uint32 timeToUpdate;
    Uint32 timeElapsed;

    Uint32* pixels;
    SDL_PixelFormat* pixelFormat;

    MapCursor* arrow;
};

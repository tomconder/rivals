#include "map.h"
#include <iostream>

Map::Map(Graphics &graphics, Level *level, int posx, int posy) :
    Sprite(graphics, posx, posy), timeToUpdate(128), timeElapsed(0) {
    cellSize = level->getCellSize();
    numCells = level->getNumCells();
    width = level->getWidth();
    height = level->getHeight();

    arrow = new MapCursor(graphics,
                          "assets/images/cursor.png",
                          0,
                          0,
                          10,
                          10,
                          0,
                          0
    );
    arrow->setupFrames();

    image = SDL_CreateTexture(graphics.getRenderer(),
                              SDL_PIXELFORMAT_RGBA32,
                              SDL_TEXTUREACCESS_TARGET,
                              width,
                              height);

    if (image == nullptr) {
        std::cout << "CreateTexture failed: " << SDL_GetError() << std::endl;
        return;
    }

    pixels = (Uint32 *)SDL_malloc(sizeof(Uint32) * width * height);
    pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);

    srcrect = {0, 0, width, height};
}

void Map::clear(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0x89, 0xcf, 0xff, 0xff);
    SDL_RenderClear(renderer);
}

void Map::drawBorders(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

    SDL_Rect rect = {0, 0, width, 1};
    SDL_RenderFillRect(renderer, &rect);

    rect = {0, height - 1, width, 1};
    SDL_RenderFillRect(renderer, &rect);

    rect = {0, 0, 1, height};
    SDL_RenderFillRect(renderer, &rect);

    rect = {width - 1, 0, 1, height};
    SDL_RenderFillRect(renderer, &rect);

    for (int y = 1; y < numCells; y++) {
        rect = {0, (y * cellSize) - 1, width, 1};
        SDL_RenderFillRect(renderer, &rect);
    }

    for (int x = 1; x < numCells; x++) {
        rect = {(x * cellSize) - 1, 0, 1, height};
        SDL_RenderFillRect(renderer, &rect);
    }
}

void Map::drawPlayer(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0xf8, 0xd7, 0xda, 0xff);

    SDL_Rect rect = {playerx * cellSize, playery * cellSize, cellSize - 1, cellSize - 1};
    SDL_RenderFillRect(renderer, &rect);
}

void Map::update(Uint32 elapsedTime, Graphics &graphics) {
    timeElapsed += elapsedTime;
    if (timeElapsed >= timeToUpdate) {
        timeElapsed = (timeElapsed - timeToUpdate) % timeToUpdate;

        SDL_Renderer *renderer = graphics.getRenderer();
        SDL_SetRenderTarget(renderer, image);

        clear(renderer);
        drawBorders(renderer);
        drawPlayer(renderer);

        arrow->setX(playerx * cellSize);
        arrow->setY(playery * cellSize);
        arrow->setDirection(playerdirection);
        arrow->draw(graphics);

//        SDL_RenderPresent(renderer);
        SDL_SetRenderTarget(renderer, nullptr);
    }
}
void Map::updatePlayer(int x, int y, direction::Direction direction) {
    playerx = x;
    playery = y;
    playerdirection = direction;
}

void Map::draw(Graphics &graphics) {
    Sprite::draw(graphics);
}

void Map::cleanup() {
    SDL_DestroyTexture(image);
    SDL_free(pixels);
}

void Map::getBounds(int &minx, int &maxx, int &miny, int &maxy) {
    minx = 0;
    maxx = numCells - 1;
    miny = 0;
    maxy = numCells - 1;
}

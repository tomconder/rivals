#include "map.hpp"
#include "file.hpp"
#include <iostream>

Map::Map(Graphics& graphics, Level* level, int posx, int posy)
    : Sprite(graphics, posx, posy), timeToUpdate(128), timeElapsed(0) {
    width = level->getWidth();
    height = level->getHeight();

    cellSize = 40;
    texWidth = level->getWidth() * cellSize;
    texHeight = level->getHeight() * cellSize;

    arrow = new MapCursor(graphics,
                          File::getResourceDir() + "/images/cursor.png",
                          0, 0, 10, 10, 0, 0);
    arrow->setupFrames();

    image = SDL_CreateTexture(graphics.getRenderer(), SDL_PIXELFORMAT_RGBA32,
                              SDL_TEXTUREACCESS_TARGET, texWidth, texHeight);

    if (image == nullptr) {
        std::cout << "CreateTexture failed: " << SDL_GetError() << std::endl;
        return;
    }

    pixels = (Uint32*)SDL_malloc(sizeof(Uint32) * texWidth * texHeight);
    pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);

    srcrect = { 0, 0, texWidth, texHeight };
}

void Map::clear(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0x89, 0xcf, 0xff, 0xff);
    SDL_RenderClear(renderer);
}

void Map::drawBorders(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

    SDL_Rect rect = { 0, 0, texWidth, 1 };
    SDL_RenderFillRect(renderer, &rect);

    rect = { 0, texHeight - 1, texWidth, 1 };
    SDL_RenderFillRect(renderer, &rect);

    rect = { 0, 0, 1, texHeight };
    SDL_RenderFillRect(renderer, &rect);

    rect = { texWidth - 1, 0, 1, texHeight };
    SDL_RenderFillRect(renderer, &rect);

    for (int y = 1; y < height; y++) {
        rect = { 0, (y * cellSize) - 1, texWidth, 1 };
        SDL_RenderFillRect(renderer, &rect);
    }

    for (int x = 1; x < width; x++) {
        rect = { (x * cellSize) - 1, 0, 1, texHeight };
        SDL_RenderFillRect(renderer, &rect);
    }
}

void Map::drawPlayer(SDL_Renderer* renderer, Player* player) {
    SDL_SetRenderDrawColor(renderer, 0xf8, 0xd7, 0xda, 0xff);

    SDL_Rect rect = { player->getX() * cellSize, player->getY() * cellSize,
                      cellSize - 1, cellSize - 1 };
    SDL_RenderFillRect(renderer, &rect);
}

void Map::drawWalls(SDL_Renderer* renderer, Level* level) {
    SDL_SetRenderDrawColor(renderer, 0xff, 0xa1, 0x00, 0xff);

    std::vector<double> values = level->getValues();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (values[x + y * width] == 1) {
                SDL_Rect rect = { x * cellSize, y * cellSize, cellSize - 1,
                                  cellSize - 1 };
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

void Map::update(Uint32 elapsedTime, Graphics& graphics, Level* level,
                 Player* player) {
    timeElapsed += elapsedTime;
    if (timeElapsed >= timeToUpdate) {
        timeElapsed = (timeElapsed - timeToUpdate) % timeToUpdate;

        SDL_Renderer* renderer = graphics.getRenderer();
        SDL_SetRenderTarget(renderer, image);

        clear(renderer);
        drawWalls(renderer, level);
        drawBorders(renderer);
        drawPlayer(renderer, player);

        arrow->setX(player->getX() * cellSize);
        arrow->setY(player->getY() * cellSize);
        arrow->setDirection(player->getDirection());
        arrow->draw(graphics);

        // SDL_RenderPresent(renderer);
        SDL_SetRenderTarget(renderer, nullptr);
    }
}

void Map::draw(Graphics& graphics) {
    Sprite::draw(graphics);
}

void Map::cleanup() {
    SDL_DestroyTexture(image);
    SDL_FreeFormat(pixelFormat);
    SDL_free(pixels);
}

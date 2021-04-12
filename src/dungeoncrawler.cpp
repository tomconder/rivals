#include "dungeoncrawler.h"

DungeonCrawler::DungeonCrawler() {
    appName = "Executive Rivals";
}

bool DungeonCrawler::onUserCreate() {
    logo = new Sprite(graphics,
                      "assets/images/coffee.png",
                      0,
                      0,
                      64,
                      64,
                      globals::SCREEN_WIDTH - 80,
                      globals::SCREEN_HEIGHT - 80);

    level = new Level(10, 40, 4, 5, direction::Direction::UP);

    map = new Map(graphics, level, 10, 10);

    player = new Player(level);

    warrior = new Warrior(graphics);
    warrior->setupAnimations();

    goblin = new Goblin(graphics);
    goblin->setupAnimations();

    return true;
}

bool DungeonCrawler::onUserUpdate(Uint32 elapsedTime) {
    if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)) {
        return false;
    }

    if (
        input.wasKeyPressed(SDL_SCANCODE_A) || input.wasKeyPressed(SDL_SCANCODE_LEFT)) {
        player->setNextMove(move::Move::LEFT);
    }
    if (input.wasKeyPressed(SDL_SCANCODE_D) || input.wasKeyPressed(SDL_SCANCODE_RIGHT)) {
        player->setNextMove(move::Move::RIGHT);
    }
    if (input.wasKeyPressed(SDL_SCANCODE_W) || input.wasKeyPressed(SDL_SCANCODE_UP)) {
        player->setNextMove(move::Move::FORWARD);
    }
    if (input.wasKeyPressed(SDL_SCANCODE_S) || input.wasKeyPressed(SDL_SCANCODE_DOWN)) {
        player->setNextMove(move::Move::BACK);
    }

    if (input.wasKeyReleased(SDL_SCANCODE_A) ||
        input.wasKeyReleased(SDL_SCANCODE_D) ||
        input.wasKeyReleased(SDL_SCANCODE_S) ||
        input.wasKeyReleased(SDL_SCANCODE_W) ||
        input.wasKeyReleased(SDL_SCANCODE_LEFT) ||
        input.wasKeyReleased(SDL_SCANCODE_RIGHT) ||
        input.wasKeyReleased(SDL_SCANCODE_UP) ||
        input.wasKeyReleased(SDL_SCANCODE_DOWN)
        ) {
        player->stopMoving();
    }

    map->update(elapsedTime, graphics);
    warrior->update(elapsedTime);
    goblin->update(elapsedTime);
    player->update(elapsedTime);

    int minx, maxx, miny, maxy;
    map->getBounds(minx, maxx, miny, maxy);
    player->handleOutOfBounds(minx, maxx, miny, maxy);
    map->updatePlayer(player->getMapX(), player->getMapY(), player->getDirection());

    map->draw(graphics);
    warrior->draw(graphics);
    goblin->draw(graphics);
    logo->draw(graphics);

    return true;
}

bool DungeonCrawler::onUserDestroy() {
    logo->cleanup();
    map->cleanup();
    warrior->cleanup();
    goblin->cleanup();

    return true;
}

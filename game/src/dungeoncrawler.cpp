#include "dungeoncrawler.hpp"
#include "file.hpp"

DungeonCrawler::DungeonCrawler() {
    appName = "Executive Rivals";
}

bool DungeonCrawler::onUserCreate() {
    logo = new Sprite(graphics, File::getResourceDir() + "/images/coffee.png",
                      0, 0, 64, 64, globals::SCREEN_WIDTH - 80,
                      globals::SCREEN_HEIGHT - 80);

    level = new Level(File::getResourceDir() + "/maps/e1m1.json");

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

    if (input.wasKeyPressed(SDL_SCANCODE_A) ||
        input.wasKeyPressed(SDL_SCANCODE_LEFT)) {
        player->setNextMove(move::Move::LEFT);
    }
    if (input.wasKeyPressed(SDL_SCANCODE_D) ||
        input.wasKeyPressed(SDL_SCANCODE_RIGHT)) {
        player->setNextMove(move::Move::RIGHT);
    }
    if (input.wasKeyPressed(SDL_SCANCODE_W) ||
        input.wasKeyPressed(SDL_SCANCODE_UP)) {
        player->setNextMove(move::Move::FORWARD);
    }
    if (input.wasKeyPressed(SDL_SCANCODE_S) ||
        input.wasKeyPressed(SDL_SCANCODE_DOWN)) {
        player->setNextMove(move::Move::BACK);
    }
    if (input.wasKeyPressed(SDL_SCANCODE_Q)) {
        player->setNextMove(move::Move::ROTATE_LEFT);
    }
    if (input.wasKeyPressed(SDL_SCANCODE_E)) {
        player->setNextMove(move::Move::ROTATE_RIGHT);
    }

    if (input.wasKeyReleased(SDL_SCANCODE_A) ||
        input.wasKeyReleased(SDL_SCANCODE_D) ||
        input.wasKeyReleased(SDL_SCANCODE_S) ||
        input.wasKeyReleased(SDL_SCANCODE_W) ||
        input.wasKeyReleased(SDL_SCANCODE_Q) ||
        input.wasKeyReleased(SDL_SCANCODE_E) ||
        input.wasKeyReleased(SDL_SCANCODE_LEFT) ||
        input.wasKeyReleased(SDL_SCANCODE_RIGHT) ||
        input.wasKeyReleased(SDL_SCANCODE_UP) ||
        input.wasKeyReleased(SDL_SCANCODE_DOWN)) {
        player->stopMoving();
    }

    map->update(elapsedTime, graphics, level, player);
    warrior->update(elapsedTime);
    goblin->update(elapsedTime);
    player->update(elapsedTime, level);

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

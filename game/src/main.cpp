#include "dungeoncrawler.hpp"
#include "globals.hpp"
#include <SDL.h>

DungeonCrawler* dungeonCrawler;

int main(int argc, char* args[]) {
    dungeonCrawler = new DungeonCrawler();

    if (dungeonCrawler->construct(globals::SCREEN_WIDTH,
                                  globals::SCREEN_HEIGHT)) {
        dungeonCrawler->start();
    }

    bool quit = false;
    while (!quit) {
        quit = dungeonCrawler->iterateLoop();
    }

    return 0;
}

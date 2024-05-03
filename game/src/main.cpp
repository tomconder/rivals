#ifdef EMSCRIPTEN
#include <emscripten/emscripten.h>
#endif
#include <SDL.h>

#include "globals.h"
#include "dungeoncrawler.h"

DungeonCrawler *dungeonCrawler;

// loop iteration is broken out like this for emscripten
bool iterateLoop() {
    return dungeonCrawler->iterateLoop();
}

int main(int argc, char *args[]) {
    dungeonCrawler = new DungeonCrawler();

    if (dungeonCrawler->construct(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT)) {
        dungeonCrawler->start();
    }

#ifdef EMSCRIPTEN
    emscripten_set_main_loop((em_callback_func) iterateLoop, 60, true);
#else
    bool quit = false;
    while (!quit) {
        quit = iterateLoop();
    }
#endif

    return 0;
}

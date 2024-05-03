#include <SDL.h>
#include <iostream>

#include "engine.hpp"

Engine::Engine() {
    appName = "undefined";
    screenWidth = globals::SCREEN_WIDTH;
    screenHeight = globals::SCREEN_HEIGHT;
    lastUpdateTime = 0;
}

globals::retcode Engine::construct(int w, int h) {
    screenWidth = w;
    screenHeight = h;

    if (screenWidth == 0 || screenHeight == 0) {
        std::cout << "Screen height or width cannot be zero" << std::endl;
        return globals::FAIL;
    }

    return globals::OK;
}

globals::retcode Engine::start() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0) {
        std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
        return globals::FAIL;
    }

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

    graphics.create(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT);

    graphics.setWindowTitle(appName);

    if (!onUserCreate()) {
        graphics.cleanup();
        return globals::OK;
    }

    lastUpdateTime = SDL_GetTicks();

    return globals::OK;
}

bool Engine::iterateLoop() {
    SDL_Event event;
    Uint32 currentTime;
    Uint32 elapsedTime;

    input.beginFrame();

    bool quit = false;
    if (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            quit = true;
        } else if (event.type == SDL_KEYDOWN) {
            if (event.key.repeat == 0) {
                input.keyDown(event);
            }
        } else if (event.type == SDL_KEYUP) {
            input.keyUp(event);
        }
    }

    graphics.clear();

    currentTime = SDL_GetTicks();
    elapsedTime = currentTime - lastUpdateTime;
    lastUpdateTime = currentTime;

    if (!onUserUpdate(elapsedTime)) {
        quit = true;
    }

    graphics.flip();

    if (quit) {
        if (onUserDestroy()) {
            graphics.cleanup();
            SDL_Quit();

            return true;
        }
    }

    return false;
}

bool Engine::onUserCreate() {
    return true;
}

bool Engine::onUserUpdate(Uint32 elapsedTime) {
    return true;
}

bool Engine::onUserDestroy() {
    return true;
}

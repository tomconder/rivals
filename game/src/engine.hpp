#pragma once

#include "globals.hpp"
#include "graphics.hpp"
#include "input.hpp"

class Engine {
   public:
    Engine();

    globals::retcode construct(int w, int h);
    globals::retcode start();

    bool iterateLoop();

    virtual bool onUserCreate();
    virtual bool onUserUpdate(Uint32 elapsedTime);
    virtual bool onUserDestroy();

    std::string appName;

   protected:
    Graphics graphics;
    Input input;
    int screenHeight;
    int screenWidth;

   private:
    Uint32 lastUpdateTime;
};

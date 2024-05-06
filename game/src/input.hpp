#pragma once

#include <SDL.h>
#include <map>

class Input {
   public:
    void beginFrame();
    void keyDown(const SDL_Event& event);
    void keyUp(const SDL_Event& event);

    bool isKeyHeld(SDL_Scancode key);
    bool wasKeyPressed(SDL_Scancode key);
    bool wasKeyReleased(SDL_Scancode key);

   private:
    std::map<SDL_Scancode, bool> heldKeys;
    std::map<SDL_Scancode, bool> pressedKeys;
    std::map<SDL_Scancode, bool> releasedKeys;
};

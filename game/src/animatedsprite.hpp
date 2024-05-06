#pragma once

#include "sprite.hpp"
#include <map>
#include <string>
#include <vector>

class AnimatedSprite : public Sprite {
   public:
    AnimatedSprite(Graphics& graphics, const std::string& file, int srcx,
                   int srcy, int w, int h, int posx, int posy,
                   Uint32 timeToUpdate);

    void playAnimation(const std::string& animation, bool once = false);
    void update(Uint32 elapsedTime) override;
    void draw(Graphics& graphics) override;

   protected:
    Uint32 timeToUpdate;
    bool currentAnimationOnce;
    std::string currentAnimation;

    void addAnimation(int frames, int x, int y, const std::string& name,
                      int width, int height, std::pair<int, int> offset);
    void resetAnimations();
    void stopAnimation();
    void setVisible(bool visible);

    virtual void setupAnimations() = 0;

   private:
    std::map<std::string, std::vector<SDL_Rect>> animations;
    std::map<std::string, std::pair<int, int>> offsets;

    int frameIndex;
    Uint32 timeElapsed;
    bool visible;
};

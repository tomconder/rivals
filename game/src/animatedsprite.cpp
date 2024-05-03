#include "animatedsprite.hpp"

AnimatedSprite::AnimatedSprite(Graphics &graphics,
                               const std::string &file,
                               int srcx,
                               int srcy,
                               int w,
                               int h,
                               int posx,
                               int posy,
                               Uint32 timeToUpdate) : Sprite(graphics,
                                                             file,
                                                             srcx,
                                                             srcy,
                                                             w,
                                                             h,
                                                             posx,
                                                             posy),
                                                      frameIndex(0),
                                                      timeToUpdate(timeToUpdate),
                                                      visible(true),
                                                      currentAnimationOnce(false),
                                                      currentAnimation("") {
    // do nothing
}

void AnimatedSprite::playAnimation(const std::string &animation, bool once) {
    currentAnimationOnce = once;
    if (currentAnimation != animation) {
        currentAnimation = animation;
        frameIndex = 0;
    }
}

void AnimatedSprite::update(Uint32 elapsedTime) {
    Sprite::update(elapsedTime);

    timeElapsed += elapsedTime;
    if (timeElapsed >= timeToUpdate) {
        timeElapsed = (timeElapsed - timeToUpdate) % timeToUpdate;
        if (frameIndex < animations[currentAnimation].size() - 1) {
            frameIndex++;
        } else {
            if (currentAnimationOnce) {
                setVisible(false);
            }
            stopAnimation();
        }
    }
}

void AnimatedSprite::draw(Graphics &graphics) {
    if (visible) {
        SDL_Rect dstrect;

        dstrect.x = x + offsets[currentAnimation].first;
        dstrect.y = y + offsets[currentAnimation].second;
        dstrect.w = srcrect.w * 2;
        dstrect.h = srcrect.h * 2;

        SDL_Rect srcrect = animations[currentAnimation][frameIndex];
        graphics.blitSurface(image, &srcrect, &dstrect);
    }
}

void AnimatedSprite::addAnimation(int frames,
                                  int x,
                                  int y,
                                  const std::string &name,
                                  int width,
                                  int height,
                                  std::pair<int, int> offset) {
    std::vector<SDL_Rect> rects;

    for (int i = 0; i < frames; i++) {
        SDL_Rect rect = {(i + x) * width, y, width, height};
        rects.push_back(rect);
    }

    animations.insert(std::pair<std::string, std::vector<SDL_Rect>>(name, rects));
    offsets.insert(std::pair<std::string, std::pair<int, int>>(name, offset));
}

void AnimatedSprite::resetAnimations() {
    animations.clear();
    offsets.clear();
}

void AnimatedSprite::stopAnimation() {
    frameIndex = 0;
}

void AnimatedSprite::setVisible(bool visible) {
    this->visible = visible;
}

void AnimatedSprite::setupAnimations() {
}

#include "enemy.h"

Enemy::Enemy(Graphics &graphics,
             const std::string &filePath,
             int sourceX,
             int sourceY,
             int width,
             int height,
             int posx,
             int posy,
             Uint32 timeToUpdate) :
    AnimatedSprite(graphics, filePath, sourceX, sourceY, width, height, posx, posy, timeToUpdate) {
    // nothing
}

void Enemy::update(Uint32 elapsedTime) {
    AnimatedSprite::update(elapsedTime);
}

void Enemy::draw(Graphics &graphics) {
    AnimatedSprite::draw(graphics);
}

Warrior::Warrior(Graphics &graphics) : Enemy(graphics,
                                             "assets/sprites/01-Warrior/Normal/Idle (96x96).png",
                                             0,
                                             0,
                                             96,
                                             96,
                                             400,
                                             120,
                                             120) {
  // nothing
}

void Warrior::update(Uint32 elapsedTime) {
    Enemy::update(elapsedTime);
}

void Warrior::draw(Graphics &graphics) {
    Enemy::draw(graphics);
}

void Warrior::setupAnimations() {
    addAnimation(4, 0, 0, "Idle", 96, 96, std::pair<int, int>(0, 0));
    playAnimation("Idle");
}

void Warrior::animationDone(const std::string &currentAnimation) {
    // nothing
}

Goblin::Goblin(Graphics &graphics) : Enemy(graphics,
                                           "assets/sprites/02-Meele Goblin/Idle (64x64).png",
                                           0,
                                           0,
                                           64,
                                           64,
                                           500,
                                           158,
                                           120) {
  // nothing
}

void Goblin::update(Uint32 elapsedTime) {
    Enemy::update(elapsedTime);
}

void Goblin::draw(Graphics &graphics) {
    Enemy::draw(graphics);
}

void Goblin::setupAnimations() {
    addAnimation(11, 0, 0, "Idle", 64, 64, std::pair<int, int>(0, 0));
    playAnimation("Idle");
}

void Goblin::animationDone(const std::string &currentAnimation) {
    // nothing
}

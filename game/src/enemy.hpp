#ifndef INCLUDE_ENEMY_H
#define INCLUDE_ENEMY_H

#include "animatedsprite.hpp"

class Enemy : public AnimatedSprite {
public:
    Enemy(Graphics &graphics,
          const std::string &file,
          int srcx,
          int srcy,
          int w,
          int h,
          int posx,
          int posy,
          Uint32 timeToUpdate);

    void update(Uint32 elapsedTime) override;
    void draw(Graphics &graphics) override;
};

class Warrior : public Enemy {
public:
    explicit Warrior(Graphics &graphics);
    void update(Uint32 elapsedTime) override;
    void draw(Graphics &graphics) override;

    void setupAnimations() override;
};

class Goblin : public Enemy {
public:
    explicit Goblin(Graphics &graphics);
    void update(Uint32 elapsedTime) override;
    void draw(Graphics &graphics) override;

    void setupAnimations() override;
};

#endif //INCLUDE_ENEMY_H

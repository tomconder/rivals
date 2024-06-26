#pragma once

#include "enemy.hpp"
#include "engine.hpp"
#include "map.hpp"
#include "player.hpp"
#include "sprite.hpp"

class DungeonCrawler : public Engine {
   public:
    DungeonCrawler();

    bool onUserCreate() override;
    bool onUserUpdate(Uint32 elapsedTime) override;
    bool onUserDestroy() override;

    Goblin* goblin;
    Level* level;
    Map* map;
    Player* player;
    Sprite* logo;
    Warrior* warrior;
};

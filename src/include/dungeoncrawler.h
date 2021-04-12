#ifndef INCLUDE_DUNGEONCRAWLER_H
#define INCLUDE_DUNGEONCRAWLER_H

#include "enemy.h"
#include "engine.h"
#include "map.h"
#include "player.h"
#include "sprite.h"

class DungeonCrawler : public Engine {
public:
    DungeonCrawler();

    bool onUserCreate() override;
    bool onUserUpdate(Uint32 elapsedTime) override;
    bool onUserDestroy() override;

    Goblin *goblin;
    Level *level;
    Map *map;
    Player *player;
    Sprite *logo;
    Warrior *warrior;
};

#endif //INCLUDE_DUNGEONCRAWLER_H

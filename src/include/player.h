#ifndef INCLUDE_PLAYER_H
#define INCLUDE_PLAYER_H

#include "globals.h"
#include "level.h"
#include <utility>
#include <SDL.h>

class Player {
public:
    Player(Level *level);

    void setNextMove(move::Move move);
    void moveBackward();
    void moveForward();
    void moveLeft();
    void moveRight();
    void rotateLeft();
    void rotateRight();
    void stopMoving();

    void handleOutOfBounds(int minx, int maxx, int miny, int maxy);
    void update(Uint32 elapsedTime);

    direction::Direction getDirection();
    int getMapX();
    int getMapY();

private:
    Uint32 timeElapsed;
    Uint32 timeToUpdate;
    move::Move nextMove;

    int mapx, mapy;
    direction::Direction direction;
};

#endif //INCLUDE_PLAYER_H

#ifndef INCLUDE_PLAYER_H
#define INCLUDE_PLAYER_H

#include "globals.hpp"
#include "level.hpp"
#include <SDL.h>

class Player {
   public:
    explicit Player(Level* level);

    void setNextMove(move::Move move);
    void moveBackward(Level* level);
    void moveForward(Level* level);
    void moveLeft(Level* level);
    void moveRight(Level* level);
    void rotateLeft();
    void rotateRight();
    void stopMoving();

    void update(Uint32 elapsedTime, Level* level);

    direction::Direction getDirection() const;
    int getX() const;
    int getY() const;

   private:
    Uint32 timeElapsed = 0;
    Uint32 timeToUpdate;
    move::Move nextMove = move::Move::NONE;

    int x, y;
    direction::Direction direction;

    bool checkDestination(int destx, int desty, Level* level);
};

#endif  // INCLUDE_PLAYER_H

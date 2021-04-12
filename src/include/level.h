#ifndef INCLUDE_LEVEL_H
#define INCLUDE_LEVEL_H

#include "globals.h"

class Level {
public:
    Level();
    Level(int numCells, int cellSize, int spawnPlayerX, int spawnPlayerY, direction::Direction spawnPlayerDirection);

    int getNumCells();
    int getCellSize();
    int getWidth();
    int getHeight();
    int getSpawnPlayerX();
    int getSpawnPlayerY();
    direction::Direction getSpawnPlayerDirection();

private:
    int numCells;
    int cellSize;
    int width = numCells * cellSize;
    int height = numCells * cellSize;

    int spawnPlayerX, spawnPlayerY;
    direction::Direction spawnPlayerDirection;
};

#endif //INCLUDE_LEVEL_H

#include "level.h"

Level::Level()
    : numCells(10), cellSize(40), spawnPlayerX(5), spawnPlayerY(8), spawnPlayerDirection(direction::Direction::UP) {
    width = numCells * cellSize;
    height = numCells * cellSize;
}

Level::Level(int numCells, int cellSize, int spawnPlayerX, int spawnPlayerY, direction::Direction spawnPlayerDirection)
    : numCells(numCells), cellSize(cellSize), spawnPlayerX(spawnPlayerX), spawnPlayerY(spawnPlayerY),
      spawnPlayerDirection(spawnPlayerDirection) {
    width = numCells * cellSize;
    height = numCells * cellSize;
}

int Level::getNumCells() {
    return numCells;
}

int Level::getCellSize() {
    return cellSize;
}

int Level::getWidth() {
    return width;
}

int Level::getHeight() {
    return height;
}

int Level::getSpawnPlayerX() {
    return spawnPlayerX;
}

int Level::getSpawnPlayerY() {
    return spawnPlayerY;
}

direction::Direction Level::getSpawnPlayerDirection() {
    return spawnPlayerDirection;
}

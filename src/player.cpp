#include <algorithm>
#include "player.h"

Player::Player(Level *level) : nextMove(move::Move::NONE), timeToUpdate(128) {
    mapx = level->getSpawnPlayerX();
    mapy = level->getSpawnPlayerY();
    direction = level->getSpawnPlayerDirection();
}

void Player::setNextMove(move::Move move) {
    nextMove = move;
}

void Player::moveBackward() {
    if (direction == direction::Direction::RIGHT) {
        mapx--;
    }
    if (direction == direction::Direction::UP) {
        mapy++;
    }
    if (direction == direction::Direction::LEFT) {
        mapx++;
    }
    if (direction == direction::Direction::DOWN) {
        mapy--;
    }
}

void Player::moveForward() {
    if (direction == direction::Direction::RIGHT) {
        mapx++;
    }
    if (direction == direction::Direction::UP) {
        mapy--;
    }
    if (direction == direction::Direction::LEFT) {
        mapx--;
    }
    if (direction == direction::Direction::DOWN) {
        mapy++;
    }
}

void Player::rotateLeft() {
    if (direction == direction::Direction::RIGHT) {
        direction = direction::Direction::UP;
    } else if (direction == direction::Direction::UP) {
        direction = direction::Direction::LEFT;
    } else if (direction == direction::Direction::LEFT) {
        direction = direction::Direction::DOWN;
    } else if (direction == direction::Direction::DOWN) {
        direction = direction::Direction::RIGHT;
    }
}

void Player::rotateRight() {
    if (direction == direction::Direction::RIGHT) {
        direction = direction::Direction::DOWN;
    } else if (direction == direction::Direction::DOWN) {
        direction = direction::Direction::LEFT;
    } else if (direction == direction::Direction::LEFT) {
        direction = direction::Direction::UP;
    } else if (direction == direction::Direction::UP) {
        direction = direction::Direction::RIGHT;
    }
}

void Player::stopMoving() {
    nextMove = move::Move::NONE;
}

void Player::handleOutOfBounds(int minx, int maxx, int miny, int maxy) {
    mapx = std::clamp(mapx, minx, maxx);
    mapy = std::clamp(mapy, miny, maxy);
}

void Player::update(Uint32 elapsedTime) {
    timeElapsed += elapsedTime;
    if (timeElapsed >= timeToUpdate) {
        timeElapsed = (timeElapsed - timeToUpdate) % timeToUpdate;
        switch (nextMove) {
        case move::Move::LEFT:
            rotateLeft();
            nextMove = move::Move::NONE;
            break;
        case move::Move::RIGHT:
            rotateRight();
            nextMove = move::Move::NONE;
            break;
        case move::Move::FORWARD:
            moveForward();
            nextMove = move::Move::NONE;
            break;
        case move::Move::BACK:
            moveBackward();
            nextMove = move::Move::NONE;
            break;
        default:break;
        }
    }
}

direction::Direction Player::getDirection() {
    return direction;
}

int Player::getMapX() {
    return mapx;
}

int Player::getMapY() {
    return mapy;
}
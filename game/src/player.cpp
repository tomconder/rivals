#include <algorithm>
#include "player.hpp"

Player::Player(Level *level) : timeToUpdate(128) {
    x = level->getSpawnPlayerX();
    y = level->getSpawnPlayerY();
    direction = level->getSpawnPlayerDirection();
    nextMove = move::Move::NONE;
}

void Player::setNextMove(move::Move move) {
    nextMove = move;
}

bool Player::checkDestination(int destx, int desty, Level *level) {
    if (destx != std::clamp(destx, 0, level->getWidth() - 1)) {
        return false;
    }

    if (desty != std::clamp(desty, 0, level->getHeight() - 1)) {
        return false;
    }

    std::vector<double> values = level->getValues();
    return values[destx + desty * level->getWidth()] != 1;
}

void Player::moveBackward(Level *level) {
    if (direction == direction::Direction::RIGHT) {
        if (checkDestination(x - 1, y, level)) {
            x--;
        }
    }
    if (direction == direction::Direction::UP) {
        if (checkDestination(x, y + 1, level)) {
            y++;
        }
    }
    if (direction == direction::Direction::LEFT) {
        if (checkDestination(x + 1, y, level)) {
            x++;
        }
    }
    if (direction == direction::Direction::DOWN) {
        if (checkDestination(x, y - 1, level)) {
            y--;
        }
    }
}

void Player::moveForward(Level *level) {
    if (direction == direction::Direction::RIGHT) {
        if (checkDestination(x + 1, y, level)) {
            x++;
        }
    }
    if (direction == direction::Direction::UP) {
        if (checkDestination(x, y - 1, level)) {
            y--;
        }
    }
    if (direction == direction::Direction::LEFT) {
        if (checkDestination(x - 1, y, level)) {
            x--;
        }
    }
    if (direction == direction::Direction::DOWN) {
        if (checkDestination(x, y + 1, level)) {
            y++;
        }
    }
}

void Player::moveLeft(Level *level) {
    if (direction == direction::Direction::RIGHT) {
        if (checkDestination(x, y - 1, level)) {
            y--;
        }
    }
    if (direction == direction::Direction::UP) {
        if (checkDestination(x - 1, y, level)) {
            x--;
        }
    }
    if (direction == direction::Direction::LEFT) {
        if (checkDestination(x, y + 1, level)) {
            y++;
        }
    }
    if (direction == direction::Direction::DOWN) {
        if (checkDestination(x + 1, y, level)) {
            x++;
        }
    }
}

void Player::moveRight(Level *level) {
    if (direction == direction::Direction::RIGHT) {
        if (checkDestination(x, y + 1, level)) {
            y++;
        }
    }
    if (direction == direction::Direction::UP) {
        if (checkDestination(x + 1, y, level)) {
            x++;
        }
    }
    if (direction == direction::Direction::LEFT) {
        if (checkDestination(x, y - 1, level)) {
            y--;
        }
    }
    if (direction == direction::Direction::DOWN) {
        if (checkDestination(x - 1, y, level)) {
            x--;
        }
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

void Player::update(Uint32 elapsedTime, Level *level) {
    timeElapsed += elapsedTime;
    if (timeElapsed >= timeToUpdate) {
        timeElapsed = (timeElapsed - timeToUpdate) % timeToUpdate;

        switch (nextMove) {
            case move::Move::BACK:
                moveBackward(level);
                break;
            case move::Move::FORWARD:
                moveForward(level);
                break;
            case move::Move::LEFT:
                moveLeft(level);
                break;
            case move::Move::RIGHT:
                moveRight(level);
                break;
            case move::Move::ROTATE_LEFT:
                rotateLeft();
                break;
            case move::Move::ROTATE_RIGHT:
                rotateRight();
                break;
            default:break;
        }

        nextMove = move::Move::NONE;
    }
}

direction::Direction Player::getDirection() const {
    return direction;
}

int Player::getX() const {
    return x;
}

int Player::getY() const {
    return y;
}

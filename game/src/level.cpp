#include "level.hpp"
#include <fstream>
#include <iostream>
#include <iterator>

Level::Level(const std::string& file) {
    initialize();
    readLevelFromFile(file);
}

int Level::getWidth() const {
    return width;
}

int Level::getHeight() const {
    return height;
}

int Level::getSpawnPlayerX() const {
    return spawnPlayerX;
}

int Level::getSpawnPlayerY() const {
    return spawnPlayerY;
}

direction::Direction Level::getSpawnPlayerDirection() const {
    return spawnPlayerDirection;
}

std::vector<double> Level::getValues() const {
    return values;
}

void Level::initialize() {
    directions[0] = direction::Direction::UP;
    directions[1] = direction::Direction::RIGHT;
    directions[2] = direction::Direction::DOWN;
    directions[3] = direction::Direction::LEFT;
}

void Level::readDirectionFromProperties(JsonValue& properties) {
    int index;
    bool isDirection = false;

    auto val = properties;
    if (val.getTag() == JSON_ARRAY) {
        auto o = begin(val);
        for (auto item : o->value) {
            if (strcmp(item->key, "value") == 0) {
                if (item->value.getTag() == JSON_NUMBER) {
                    index = (int)(item->value).toNumber();
                }
            } else if (strcmp(item->key, "name") == 0) {
                if (item->value.getTag() == JSON_STRING) {
                    if (strcmp(item->value.toString(), "direction") == 0) {
                        isDirection = true;
                    }
                }
            }
        }

        if (isDirection && index >= 0 && index < 4) {
            spawnPlayerDirection = directions[index];
        } else {
            spawnPlayerDirection = direction::Direction::UP;
        }
    }
}

void Level::readLevelFromFile(const std::string& file) {
    std::ifstream mapFile(file, std::ios::binary);
    std::vector<char> contents;
    std::copy(std::istream_iterator<char>(mapFile),
              std::istream_iterator<char>(), std::back_inserter(contents));

    char* endptr;
    JsonValue value;
    JsonAllocator allocator;
    int status = jsonParse(contents.data(), &endptr, &value, allocator);
    if (status != JSON_OK) {
        std::cout << "Error reading level - " << file << ": "
                  << jsonStrError(status) << " at " << endptr - contents.data()
                  << std::endl;
        return;
    }

    int tilewidth;
    int tileheight;
    int x, y;

    for (auto i : value) {
        if (strcmp(i->key, "height") == 0) {
            height = (int)(i->value).toNumber();
        } else if (strcmp(i->key, "width") == 0) {
            width = (int)(i->value).toNumber();
        } else if (strcmp(i->key, "layers") == 0) {
            JsonValue o = i->value;
            readLevelFromLayers(o, &x, &y);
        } else if (strcmp(i->key, "tileheight") == 0) {
            if (i->value.getTag() == JSON_NUMBER) {
                tileheight = (int)(i->value).toNumber();
            }
        } else if (strcmp(i->key, "tilewidth") == 0) {
            if (i->value.getTag() == JSON_NUMBER) {
                tilewidth = (int)(i->value).toNumber();
            }
        }
    }

    spawnPlayerX = (int)x / tilewidth;
    spawnPlayerY = (int)y / tileheight;
}

void Level::readLevelFromLayers(JsonValue& layers, int* x, int* y) {
    bool isPlayerLayer;
    bool isTileLayer;
    int temph = 0;
    int tempw = 0;
    int tempx = 0;
    int tempy = 0;

    for (auto l : layers) {
        isTileLayer = false;
        isPlayerLayer = false;

        for (auto i : l->value) {
            if (strcmp(i->key, "type") == 0) {
                if (strcmp(i->value.toString(), "tilelayer") == 0) {
                    isTileLayer = true;
                }
            } else if (strcmp(i->key, "name") == 0) {
                if (strcmp(i->value.toString(), "player") == 0) {
                    isPlayerLayer = true;
                }
            } else if (strcmp(i->key, "data") == 0) {
                auto val = i->value;
                if (val.getTag() == JSON_ARRAY) {
                    for (auto item : val) {
                        if (item->value.getTag() == JSON_NUMBER) {
                            values.push_back((item->value).toNumber());
                        }
                    }
                }
            } else if (strcmp(i->key, "objects") == 0) {
                auto val = i->value;
                if (val.getTag() == JSON_ARRAY) {
                    auto o = begin(val);
                    for (auto item : o->value) {
                        if (strcmp(item->key, "x") == 0) {
                            if (item->value.getTag() == JSON_NUMBER) {
                                tempx = (int)(item->value).toNumber();
                            }
                        } else if (strcmp(item->key, "y") == 0) {
                            if (item->value.getTag() == JSON_NUMBER) {
                                tempy = (int)(item->value).toNumber();
                            }
                        } else if (strcmp(item->key, "properties") == 0) {
                            if (item->value.getTag() == JSON_ARRAY) {
                                readDirectionFromProperties(item->value);
                            }
                        }
                    }
                }
            } else if (strcmp(i->key, "height") == 0) {
                temph = (int)(i->value).toNumber();
            } else if (strcmp(i->key, "width") == 0) {
                tempw = (int)(i->value).toNumber();
            }
        }

        if (isTileLayer) {
            height = temph;
            width = tempw;
        } else if (isPlayerLayer) {
            *x = tempx;
            *y = tempy;
        }
    }
}

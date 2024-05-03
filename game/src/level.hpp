#ifndef INCLUDE_LEVEL_H
#define INCLUDE_LEVEL_H

#include "gason.hpp"
#include "globals.hpp"
#include <map>
#include <string>
#include <vector>

class Level {
public:
    explicit Level(const std::string &file);

    int getWidth() const;
    int getHeight() const;
    int getSpawnPlayerX() const;
    int getSpawnPlayerY() const;
    direction::Direction getSpawnPlayerDirection() const;
    std::vector<double> getValues() const;

private:
    int width{10};
    int height{10};
    std::vector<double> values;
    std::map<double, direction::Direction> directions;

    int spawnPlayerX{0}, spawnPlayerY{0};
    direction::Direction spawnPlayerDirection;

    void initialize();
    void readDirectionFromProperties(JsonValue &properties);
    void readLevelFromFile(const std::string &file);
    void readLevelFromLayers(JsonValue &layers, int *x, int *y);
};

#endif //INCLUDE_LEVEL_H

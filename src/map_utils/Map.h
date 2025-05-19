#ifndef MAP_H
#define MAP_H

#include <unordered_map>
#include "map_elements/Element.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "./map_elements/Ground.h"
#include "./map_elements/Platform.h"
#include "./map_elements/Start.h"
#include "./map_elements/Exit.h"
#include "./map_elements/Spikes.h"
#include "../level_utils/LevelParser.h"
#include <ranges>
#include "../level_utils/LevelInterface.h"

class Map {
private:
    std::unordered_map<int, std::unique_ptr<Element>> map_content;
    LevelParser::LevelInfo level_info;
    bool level_started;

public:
    Map();

    auto getMapContent() -> std::unordered_map<int, std::unique_ptr<Element>>&;
    auto clearMapContent() -> void;

    auto draw(sf::RenderWindow& window, Player& player) -> void;
    auto generate(int chapter, int level, sf::RenderWindow& window, Player& player) -> void;

    auto start(Player& player) -> void;
    auto stop() -> void;

    auto getLevelStarted() -> bool;
    auto setLevelStarted(bool value) -> void;
};

#endif //MAP_H
//
// Created by kame on 5/6/25.
//

#ifndef MAP_H
#define MAP_H

#include <unordered_map>
#include "map_elements/Element.h"
#include <SFML/Graphics.hpp>
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
    std::unordered_map<int, Element*> map_content;
    sf::RenderWindow *window;
    LevelParser::LevelInfo level_info;
    Player *player;
    bool level_started;

public:
    Map(sf::RenderWindow &window, Player &player);

    auto getMapContent() -> std::unordered_map<int, Element*>;

    auto draw() -> void;
    auto generate(int chapter, int level) -> void;

    auto start() -> void;
    auto stop() -> void;
};



#endif //MAP_H

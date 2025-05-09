//
// Created by kame on 5/6/25.
//

#ifndef MAP_H
#define MAP_H

#include <unordered_map>
#include "Element.h"
#include <SFML/Graphics.hpp>
#include "Ground.h"
#include "Platform.h"
#include "Start.h"
#include "Exit.h"
#include "Spikes.h"
#include "../level_utils/LevelParser.h"
#include <ranges>


class Map {
private:
    std::unordered_map<int, Element*> map_content;
    sf::RenderWindow *window;
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

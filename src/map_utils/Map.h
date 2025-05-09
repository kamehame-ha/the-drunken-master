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
#include "../level_utils/LevelParser.h"


class Map {
private:
    std::unordered_map<int, Element*> map_content;
    sf::RenderWindow *window;
    Player *player;

public:
    Map(sf::RenderWindow &window, Player &player);

    auto getMapContent() -> std::unordered_map<int, Element*>;

    auto draw() -> void;
    auto generate(int chapter, int level) -> void;
};



#endif //MAP_H

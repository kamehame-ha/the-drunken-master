//
// Created by kame on 5/6/25.
//

#ifndef MAP_H
#define MAP_H
#include <unordered_map>

#include "Element.h"
#include <SFML/Graphics.hpp>


class Map {
private:
    std::unordered_map<int, Element> map_content;
    sf::RenderWindow *window;

public:
    Map(sf::RenderWindow &window);
};



#endif //MAP_H

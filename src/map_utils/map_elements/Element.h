//
// Created by kame on 5/6/25.
//

#ifndef ELEMENT_H
#define ELEMENT_H

#include <SFML/Graphics.hpp>
#include "../../entity/Player.h"

class Element {
private:
    // default shape
    sf::RectangleShape shape;

public:
    virtual ~Element() = default;

    Element();

    virtual auto checkCollision(Player &player) -> bool;

    virtual auto getShape() -> sf::RectangleShape&;

    virtual auto create(Player &player, sf::RenderWindow &window) -> void;

    virtual auto autoPlaceVirtualShape() -> void;

    virtual auto getVirtualShape() -> sf::RectangleShape&;
};



#endif //ELEMENT_H

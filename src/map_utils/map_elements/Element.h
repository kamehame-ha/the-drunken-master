//
// Created by kame on 5/6/25.
//

#ifndef ELEMENT_H
#define ELEMENT_H

#include <SFML/Graphics.hpp>
#include "../../entity/Player.h"

class Element {
private:
    sf::RenderWindow *window;
    // needed for custom player interactions
    Player *player;

    // default shape
    sf::RectangleShape shape;

public:
    virtual ~Element() = default;

    Element(sf::RenderWindow &window, Player &player);

    virtual auto checkCollision() -> bool;

    virtual auto getShape() -> sf::RectangleShape&;

    virtual auto create() -> void;

    virtual auto autoPlaceVirtualShape() -> void;

    virtual auto getVirtualShape() -> sf::RectangleShape&;
};



#endif //ELEMENT_H

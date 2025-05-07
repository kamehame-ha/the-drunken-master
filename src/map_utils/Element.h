//
// Created by kame on 5/6/25.
//

#ifndef ELEMENT_H
#define ELEMENT_H

#include <SFML/Graphics.hpp>
#include "../Player.h"



class Element {
private:
    sf::RenderWindow *window;
    // needed for custom player interactions
    Player *player;

    // default shape
    sf::RectangleShape shape;

public:
    Element(sf::RenderWindow &window, Player &player);

    auto checkCollision() -> bool;
    auto resolveCollision() -> void;

    auto getShape() -> sf::RectangleShape&;
    auto create() -> void;
};



#endif //ELEMENT_H

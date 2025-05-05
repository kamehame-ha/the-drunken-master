//
// Created by kame on 4/25/25.
//

#ifndef HITBOX_H
#define HITBOX_H

#include <SFML/Graphics.hpp>
#include "Player.h"


class Hitbox {
private:
    sf::RenderWindow* window;

public:
    explicit Hitbox(sf::RenderWindow &window);

    auto check(auto item) -> void;
};



#endif //HITBOX_H

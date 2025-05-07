//
// Created by kame on 4/25/25.
//

#ifndef HITBOX_H
#define HITBOX_H

#include <SFML/Graphics.hpp>
#include "Map.h"

class Player;

class Hitbox {
private:
    sf::RenderWindow* window;
    Player* player;

    auto check() const -> void;
    auto check(Map &map) const -> void;

public:
    explicit Hitbox(sf::RenderWindow &window, Player &player);

    auto resolveGlobalCollision(float deltaTime, Map &map) const -> void;
};



#endif //HITBOX_H

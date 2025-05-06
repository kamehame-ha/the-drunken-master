//
// Created by kame on 4/25/25.
//

#ifndef HITBOX_H
#define HITBOX_H

#include <SFML/Graphics.hpp>

class Player;

class Hitbox {
private:
    sf::RenderWindow* window;
    Player* player;

public:
    explicit Hitbox(sf::RenderWindow &window, Player &player);

    auto check() const -> void;
};



#endif //HITBOX_H

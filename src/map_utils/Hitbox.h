#ifndef HITBOX_H
#define HITBOX_H

#include <SFML/Graphics.hpp>
#include "Map.h"
#include "../entity/Player.h"
#include "fmt/printf.h"

class Player;

class Hitbox {
private:
    auto check(sf::RenderWindow& window, Player& player) const -> void;
    auto check(Map &map, Player& player) const -> void;
    static auto resolveDefaultCollision(Player &player, Element &element) -> void;

public:
    Hitbox();

    auto resolveGlobalCollision(float deltaTime, Map &map, sf::RenderWindow& window, Player& player) const -> void;
};

#endif //HITBOX_H
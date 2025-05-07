//
// Created by kame on 4/25/25.
//

#include "Hitbox.h"
#include "../Player.h"
#include "fmt/printf.h"

Hitbox::Hitbox(sf::RenderWindow &window, Player &player): window(&window) {
    this->window = &window;
    this->player = &player;
}

auto Hitbox::check() const -> void {
    const auto& shape = player->getShape();
    const float radius = shape.getRadius();
    const sf::Vector2f position = shape.getPosition();
    const sf::Vector2u w_size = window->getSize();

    // Calculate constrained position
    float newX = position.x;
    float newY = position.y;

    // Constrain X position
    if (position.x < 0) {
        // Left
        newX = 0;
        player->stopX();
    }
    else if (position.x + (radius * 2) > w_size.x) {
        // Right
        newX = w_size.x - (radius * 2);
        player->stopX();
    }

    // Constrain Y position
    if (position.y < 0) {
        // Top
        newY = 0;
        player->stopY();
    }
    else if (position.y + (radius * 2) > w_size.y) {
        // Bottom
        newY = w_size.y - (radius * 2);
        player->stopY();
        player->setOnGround(true);
        player->setCanJump(true);
    }

    // Apply the constrained position if needed
    if (newX != position.x || newY != position.y) {
        player->setPosition(newX, newY);
    }
}

auto Hitbox::check(Map &map) const -> void {
    for (auto& [i, element] : map.getMapContent()) {
        if (element.checkCollision()) {
            auto el_shape = element.getShape();
            auto pl_shape = player->getShape();

            player->stopY();
            player->setOnGround(true);
            player->setCanJump(true);
            player->setOnElement(true);
            player->setPosition(pl_shape.getPosition().x, el_shape.getPosition().y - (2 * pl_shape.getRadius()));
        } else {
            player->setOnElement(false);
        }
    }
}

auto Hitbox::resolveGlobalCollision(float deltaTime, Map &map) const -> void {
    player->update(deltaTime);
    check();
    player->update(deltaTime);
    check(map);
}



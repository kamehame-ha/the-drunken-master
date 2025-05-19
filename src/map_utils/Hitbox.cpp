//
// Created by kame on 4/25/25.
//

#include "Hitbox.h"


Hitbox::Hitbox() = default;

auto Hitbox::check(sf::RenderWindow& window, Player& player) const -> void {
    const auto& shape = player.getShape();
    const float radius = shape.getRadius();
    const sf::Vector2f position = shape.getPosition();
    const sf::Vector2u w_size = window.getSize();

    // Calculate constrained position
    float newX = position.x;
    float newY = position.y;

    // Constrain X position
    if (position.x < 0) {
        // Left
        newX = 0;
        player.stopX();
    }
    else if (position.x + (radius * 2) > w_size.x) {
        // Right
        newX = w_size.x - (radius * 2);
        player.stopX();
    }

    // Constrain Y position
    if (position.y < 0) {
        // Top
        newY = 0;
        player.stopY();
    }
    else if (position.y + (radius * 2) > w_size.y) {
        // Bottom
        newY = w_size.y - (radius * 2);
        player.stopY();
        player.setOnGround(true);
        player.setCanJump(true);
    }

    // Apply the constrained position if needed
    if (newX != position.x || newY != position.y) {
        player.setPosition(newX, newY);
    }
}

auto Hitbox::check(Map &map, Player& player) const -> void {
    for (auto& [i, element] : map.getMapContent()) {
        if (element->checkCollision(player)) {
            if (dynamic_cast<Start*>(element.get())) {
                // No logic, just disabled collision
            } else if (dynamic_cast<Exit*>(element.get())) {
                auto el_shape = element->getShape();
                auto pl_shape = player.getShape();
                player.stopY();
                player.setPosition(el_shape.getPosition().x, el_shape.getPosition().y);
                map.setLevelStarted(false);
            } else if (dynamic_cast<Spikes*>(element.get())) {
                auto start = std::ranges::find_if(map.getMapContent(), [](auto& pair) {
                    return dynamic_cast<Start*>(pair.second.get());
                });

                auto& shape = start->second->getShape();
                player.setPosition(shape.getPosition().x, shape.getPosition().y);
                auto& player_data = player.getPlayerData();
                player_data.hp = player_data.hp - (20 + Dice(10).roll());

                if (player_data.hp < 0) {
                    player_data.hp = 0;
                }

                player.setPlayerData(player_data);

                auto game_save = GameSave();
                game_save.save(player.getPlayerData());

            } else {
                resolveDefaultCollision(player, *element);
            }
        } else {
            player.setOnElement(false);
        }
    }
}

auto Hitbox::resolveDefaultCollision(Player &player, Element &element) -> void {
    auto el_shape = element.getShape();
    auto pl_shape = player.getShape();

    if (pl_shape.getPosition().y < el_shape.getPosition().y) {
        player.stopY();
        player.setOnGround(true);
        player.setCanJump(true);
        player.setOnElement(true);

        player.setPosition(pl_shape.getPosition().x, el_shape.getPosition().y - (2 * pl_shape.getRadius()));
    } else {
        player.setPosition(pl_shape.getPosition().x, el_shape.getPosition().y + el_shape.getSize().y);
    }
}


auto Hitbox::resolveGlobalCollision(float deltaTime, Map &map, sf::RenderWindow& window, Player& player) const -> void {
    player.update(deltaTime);
    check(window, player);
    player.update(deltaTime);
    check(map, player);
}



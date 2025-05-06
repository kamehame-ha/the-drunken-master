//
// Created by kame on 5/6/25.
//

#include "Element.h"

#include "fmt/format.h"

Element::Element(sf::RenderWindow &window, Player &player): window(&window), player() {
    this->player = &player;
    this->window = &window;
}

// Base version stops player from going through element
auto Element::checkCollision() -> void {
    auto& shape = player->getShape();
    const float radius = shape.getRadius();
    sf::Vector2f position = shape.getPosition();

    const auto element = this->shape;
    auto element_size = element.getSize();
    auto element_position = element.getPosition();

    std::pair<float, float> hitbox_line;

    // Element hitbox line
    // by default if x > y, x is a hitbox line

    hitbox_line = std::make_pair(element_position.x, element_size.x + element_position.x);

    if (position.x > hitbox_line.first && position.x < hitbox_line.second) {
        fmt::println("Player is in the hitbox line");
        if ((position.y + (2 * radius)) < element_position.y) {
            // Player is on top of the element
            shape.setPosition(sf::Vector2f(position.x ,element_position.y - (2 * radius)));
            player->setOnGround(true);
            player->setCanJump(true);
            player->stopY();
        }
    }

    // Left/right collision check

    // Top/bottom collision check
}

auto Element::create() -> void {
    const sf::RectangleShape r(sf::Vector2f(250.0f, 50.0f));
    shape = r;
    shape.setFillColor(sf::Color::Green);
}

auto Element::getShape() -> sf::RectangleShape& {
    return shape;
}


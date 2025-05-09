//
// Created by kame on 5/6/25.
//

#ifndef PLATFORM_H
#define PLATFORM_H
#include "Element.h"


class Platform : public Element {
private:
    sf::RenderWindow *window;
    // needed for custom player interactions
    Player *player;

    sf::RectangleShape hitbox_shape;

    bool passthrough;

public:
    Platform(sf::RenderWindow &window, Player &player): Element(window, player), hitbox_shape() {
        this->window = &window;
        this->player = &player;
    };

    void create() override {
        Element::create();
        const sf::RectangleShape h(sf::Vector2f(150.0f, 0.5f));
        hitbox_shape = h;
        hitbox_shape.setFillColor(sf::Color::Red);

        getShape().setSize(sf::Vector2f(150.0f, 25.0f));
        getShape().setFillColor(sf::Color(56,29,12));
    }

    bool checkCollision() override {
        auto& shape = player->getShape();
        const float radius = shape.getRadius();
        sf::Vector2f position = shape.getPosition();

        const auto element = getVirtualShape();
        auto element_size = element.getSize();
        auto element_position = element.getPosition();

        std::pair<float, float> hitbox_line;

        // Element hitbox line
        // by default if x > y, x is a hitbox line

        hitbox_line = std::make_pair(element_position.x, element_size.x + element_position.x);

        if (position.x + radius > hitbox_line.first && position.x + radius < hitbox_line.second) {
            if (element_position.y > position.y + (radius * 2)) {
                // Player is above platform
                passthrough = false;
            }

            if (element_position.y < position.y) {
                // Player is below platform
                passthrough = true;
            }

            if (element.getGlobalBounds().findIntersection(shape.getGlobalBounds()) && !passthrough) {
                return true;
            }
        } else return false;

        return false;
    }

    sf::RectangleShape& getShape() override {
        return Element::getShape();
    }

    sf::RectangleShape& getVirtualShape() override {
        return this->hitbox_shape;
    }

    void autoPlaceVirtualShape() override {
        this->hitbox_shape.setPosition(sf::Vector2f(getShape().getPosition().x, getShape().getPosition().y - this->hitbox_shape.getSize().y));
    }
};



#endif //PLATFORM_H

//
// Created by kame on 5/9/25.
//

#ifndef START_H
#define START_H
#include "Element.h"


class Start : public Element {
public:
    Start() = default;

    void create(Player &player, sf::RenderWindow &window) override {
        Element::create(player, window);
        getShape().setFillColor(sf::Color::Transparent);
        getShape().setSize(sf::Vector2f(player.getShape().getRadius() * 2, player.getShape().getRadius() * 2));
    }
};


#endif //START_H

//
// Created by kame on 5/6/25.
//

#ifndef EXIT_H
#define EXIT_H
#include "Element.h"


class Exit : public Element {

public:
    Exit() = default;

    void create(Player &player, sf::RenderWindow &window) override {
        Element::create(player, window);
        getShape().setFillColor(sf::Color::Blue);
        getShape().setSize(sf::Vector2f(player.getShape().getRadius() * 2, player.getShape().getRadius() * 2));
    }
};



#endif //EXIT_H

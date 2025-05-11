//
// Created by kame on 5/6/25.
//

#ifndef EXIT_H
#define EXIT_H
#include "Element.h"


class Exit : public Element {
private:
    sf::RenderWindow *window;
    // needed for custom player interactions
    Player *player;

    sf::RectangleShape hitbox_shape;

public:
    Exit(sf::RenderWindow &window, Player &player): Element(window, player) {
        this->window = &window;
        this->player = &player;
    }

    void create() override {
        Element::create();
        getShape().setFillColor(sf::Color::Blue);
        getShape().setSize(sf::Vector2f(player->getShape().getRadius() * 2, player->getShape().getRadius() * 2));
    }
};



#endif //EXIT_H

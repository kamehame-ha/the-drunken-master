//
// Created by kame on 5/6/25.
//

#ifndef GROUND_H
#define GROUND_H
#include "Element.h"


class Ground : public Element {
private:
    sf::RenderWindow *window;
    // needed for custom player interactions
    Player *player;

public:
    Ground(sf::RenderWindow &window, Player &player): Element(window, player) {
        this->window = &window;
        this->player = &player;
    };

    void create() override {
        Element::create();
        getShape().setSize(sf::Vector2f(window->getSize().x, 50.0f));
        getShape().setFillColor(sf::Color(107,54,21));
        getShape().setPosition(sf::Vector2f(0, window->getSize().y - getShape().getSize().y));
    }
};



#endif //GROUND_H

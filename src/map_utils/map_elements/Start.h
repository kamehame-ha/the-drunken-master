//
// Created by kame on 5/9/25.
//

#ifndef START_H
#define START_H
#include "Element.h"


class Start : public Element {
private:
    sf::RenderWindow *window;
    Player *player;

public:
    Start(sf::RenderWindow &window, Player &player) : Element(window, player) {
        this->window = &window;
        this->player = &player;
    };

    void create() override {
        Element::create();
        getShape().setFillColor(sf::Color::Green);
        getShape().setSize(sf::Vector2f(60.0f, 60.0f));
    }
};


#endif //START_H

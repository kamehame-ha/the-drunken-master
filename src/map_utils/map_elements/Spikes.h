//
// Created by kame on 5/6/25.
//

#ifndef SPIKES_H
#define SPIKES_H
#include "Element.h"


class Spikes : public Element {
private:
    sf::RenderWindow* window;
    Player *player;
    sf::Texture texture;

public:
    Spikes(sf::RenderWindow &window, Player &player): Element(window, player) {
        this->window = &window;
        this->player = &player;

        if (!texture.loadFromFile("../../assets/textures/spike.png")) {
            fmt::print("Failed to load spike texture\n");
        }
        texture.setRepeated(true);
        texture.setSmooth(true);
    }

    void create() override {
        Element::create();
        getShape().setSize(sf::Vector2f(150.0f, 50.0f));
        getShape().setFillColor(sf::Color(72,72,72));
        getShape().setTexture(&texture);
    }

    bool checkCollision() override {
        return false;
    }
};



#endif //SPIKES_H

//
// Created by kame on 5/6/25.
//

#ifndef SPIKES_H
#define SPIKES_H
#include "Element.h"


class Spikes : public Element {
private:
    sf::Texture texture;

public:
    Spikes() {
        if (!texture.loadFromFile("../../assets/textures/spike.png")) {
            fmt::print("Failed to load spike texture\n");
        }
        texture.setRepeated(true);
        texture.setSmooth(true);
    }

    void create(Player &player, sf::RenderWindow &window) override {
        Element::create(player, window);
        getShape().setSize(sf::Vector2f(150.0f, 50.0f));
        getShape().setFillColor(sf::Color(72,72,72));
        getShape().setTexture(&texture);
    }
};



#endif //SPIKES_H

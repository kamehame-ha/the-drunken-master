//
// Created by kame on 4/25/25.
//

#include "Wrapper.h"

Wrapper::Wrapper() = default;

auto Wrapper::bounds(auto item) -> sf::FloatRect {
    return  item.getLocalBounds();
}


auto Wrapper::center(auto item, sf::RenderWindow &window) -> std::pair<float, float> {
    const sf::FloatRect b = bounds(item);

    float centerX = (window.getSize().x / 2) - (b.size.x / 2);
    float centerY = (window.getSize().y / 2) - (b.size.y / 2);

    return std::make_pair(centerX, centerY);
}

template std::pair<float, float> Wrapper::center<sf::Text>(sf::Text, sf::RenderWindow &window);
template std::pair<float, float> Wrapper::center<sf::Sprite>(sf::Sprite, sf::RenderWindow &window);
template std::pair<float, float> Wrapper::center<sf::CircleShape>(sf::CircleShape, sf::RenderWindow &window);

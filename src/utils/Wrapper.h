//
// Created by kame on 4/25/25.
//

#ifndef WRAPPER_H
#define WRAPPER_H

#include <SFML/Graphics.hpp>

class Wrapper {
public:
    explicit Wrapper();

    auto center(auto item, sf::RenderWindow &window) -> std::pair<float, float>;

    static auto bounds(auto item) -> sf::FloatRect;
};



#endif //WRAPPER_H

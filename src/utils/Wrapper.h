//
// Created by kame on 4/25/25.
//

#ifndef WRAPPER_H
#define WRAPPER_H

#include <SFML/Graphics.hpp>

class Wrapper {
private:
    sf::RenderWindow* window;

public:
    explicit Wrapper(sf::RenderWindow &window);

    auto center(auto item) -> std::pair<float, float>;

    static auto bounds(auto item) -> sf::FloatRect;
};



#endif //WRAPPER_H

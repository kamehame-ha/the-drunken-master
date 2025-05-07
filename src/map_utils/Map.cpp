//
// Created by kame on 5/6/25.
//

#include "Map.h"

Map::Map(sf::RenderWindow &window, Player &player): window(&window), player() {
    this->player = &player;
    this->window = &window;

    // Dev test only
    Element el = Element(window, player);
    el.create();

    el.getShape().setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 + 250));

    map_content.insert(std::pair<int, Element>(0, el));
}

auto Map::getMapContent() -> std::unordered_map<int, Element> {
    return map_content;
}

auto Map::draw() -> void {
    for (auto& [i, element] : map_content) {
        window->draw(element.getShape());
    }
}



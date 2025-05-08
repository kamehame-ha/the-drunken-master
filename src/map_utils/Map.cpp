//
// Created by kame on 5/6/25.
//

#include "Map.h"

Map::Map(sf::RenderWindow &window, Player &player): window(&window), player() {
    this->player = &player;
    this->window = &window;

    // Create and initialize elements properly
    Element* el = new Platform(window, player);
    el->create();
    el->getShape().setPosition(sf::Vector2f(window.getSize().x / 2 + 300, window.getSize().y / 2 + 260));

    Element* el2 = new Platform(window, player);
    el2->create();
    el2->getShape().setPosition(sf::Vector2f(300, window.getSize().y / 2 + 200));

    Element* ground = new Ground(window, player);
    ground->create();

    map_content.insert(std::pair(0, el));
    map_content.insert(std::pair(1, ground));
    map_content.insert(std::pair(2, el2));
}

auto Map::getMapContent() -> std::unordered_map<int, Element *> {
    return map_content;
}

auto Map::setMapContent(const std::unordered_map<int, Element *> &map_content) {
    this->map_content = map_content;
}


auto Map::draw() -> void {
    for (auto& [i, element] : map_content) {
        if (dynamic_cast<Platform*>(element)) {
            window->draw(element->getShape());
            element->autoPlaceVirtualShape();
            window->draw(element->getVirtualShape());
        } else {
            window->draw(element->getShape());
        }
    }
}



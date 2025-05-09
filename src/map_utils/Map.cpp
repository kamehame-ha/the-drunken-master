//
// Created by kame on 5/6/25.
//

#include "Map.h"

Map::Map(sf::RenderWindow &window, Player &player): window(&window), player() {
    this->player = &player;
    this->window = &window;
}

auto Map::getMapContent() -> std::unordered_map<int, Element*> {
    return map_content;
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

auto Map::generate(int chapter, int level) -> void {
    auto info = LevelParser("level_" + std::to_string(chapter) + "_" + std::to_string(level) + ".txt").parse();
    int i = 0;
    for (auto& obj : info.objects) {
        switch (obj.name) {
            case "ground":
                auto ground = new Ground(*window, *player);
                ground->create();
                auto g_shape = ground->getShape();

                if (obj.size_y != 0.0f) {
                    g_shape.setSize(sf::Vector2f(g_shape.getSize().x, obj.size_y));
                }

                map_content.insert(std::pair<int, Element*>(i, ground));
                break;
            case "platform":
                auto* platform = new Platform(*window, *player);
                platform->create();
                auto p_shape = platform->getShape();

                if (obj.position_x != 0.0f) {
                    p_shape.setPosition(sf::Vector2f(obj.position_x, p_shape.getPosition().y));
                }

                if (obj.position_y != 0.0f) {
                    p_shape.setPosition(sf::Vector2f(p_shape.getPosition().x, obj.position_y));
                }

                if (obj.size_x != 0.0f) {
                    p_shape.setSize(sf::Vector2f(obj.size_x, p_shape.getSize().y));
                }

                if (obj.size_y != 0.0f) {
                    p_shape.setSize(sf::Vector2f(p_shape.getSize().x, obj.size_y));
                }

                map_content.insert(std::pair<int, Element*>(i, platform));
                break;

            default: break;
        }
        i++;
    }
}



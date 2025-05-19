//
// Created by kame on 5/6/25.
//

#include "Map.h"

Map::Map(): level_info() {
    level_started = false;
}

auto Map::getMapContent() -> std::unordered_map<int, std::unique_ptr<Element>>& {
    return map_content;
}
auto Map::draw(sf::RenderWindow& window, Player& player) -> void {
    for (auto& [i, element] : map_content) {
        if (dynamic_cast<Platform*>(element.get())) {
            window.draw(element->getShape());
            element->autoPlaceVirtualShape();
            window.draw(element->getVirtualShape());
        } else {
            window.draw(element->getShape());
        }
    }

    auto interface = LevelInterface();
    interface.show(window, player, level_info);
}

auto Map::generate(int chapter, int level, sf::RenderWindow& window, Player& player) -> void {
    clearMapContent();
    auto info = LevelParser("level_" + std::to_string(chapter) + "-" + std::to_string(level) + ".txt").parse();
    level_info = info;
    int i = 0;
    for (auto& obj : info.objects) {
        if (obj.name == "ground") {
            auto ground = std::make_unique<Ground>();
            ground->create(player, window);
            auto& g_shape = ground->getShape();

            if (obj.size_y != 0.0f) {
                g_shape.setSize(sf::Vector2f(g_shape.getSize().x, obj.size_y));
            }

            map_content.emplace(i, std::move(ground));
        } else if (obj.name == "platform") {
            auto platform = std::make_unique<Platform>();
            platform->create(player, window);
            auto& p_shape = platform->getShape();
            auto& pv_shape = platform->getVirtualShape();

            if (obj.position_x != 0.0f) {
                p_shape.setPosition(sf::Vector2f(obj.position_x, p_shape.getPosition().y));
            }

            if (obj.position_y != 0.0f) {
                p_shape.setPosition(sf::Vector2f(p_shape.getPosition().x, obj.position_y));
            }

            if (obj.size_x != 0.0f) {
                p_shape.setSize(sf::Vector2f(obj.size_x, p_shape.getSize().y));
                pv_shape.setSize(sf::Vector2f(obj.size_x, pv_shape.getSize().y));
            }

            if (obj.size_y != 0.0f) {
                p_shape.setSize(sf::Vector2f(p_shape.getSize().x, obj.size_y));
            }

            platform->autoPlaceVirtualShape();

            map_content.emplace(i, std::move(platform));
        } else if (obj.name == "start") {
            auto start = std::make_unique<Start>();
            start->create(player, window);
            auto& s_shape = start->getShape();

            if (obj.position_x != 0.0f) {
                s_shape.setPosition(sf::Vector2f(obj.position_x, s_shape.getPosition().y));
            }

            if (obj.position_y != 0.0f) {
                s_shape.setPosition(sf::Vector2f(s_shape.getPosition().x, obj.position_y));
            }

            map_content.emplace(i, std::move(start));
        } else if (obj.name == "exit") {
            auto exit = std::make_unique<Exit>();
            exit->create(player, window);
            auto& e_shape = exit->getShape();

            if (obj.position_x != 0.0f) {
                e_shape.setPosition(sf::Vector2f(obj.position_x, e_shape.getPosition().y));
            }

            if (obj.position_y != 0.0f) {
                e_shape.setPosition(sf::Vector2f(e_shape.getPosition().x, obj.position_y));
            }

            map_content.emplace(i, std::move(exit));
        } else if (obj.name == "spikes") {
            auto spikes = std::make_unique<Spikes>();
            spikes->create(player, window);
            auto& s_shape = spikes->getShape();

            if (obj.position_x != 0.0f) {
                s_shape.setPosition(sf::Vector2f(obj.position_x, s_shape.getPosition().y));
            }

            if (obj.position_y != 0.0f) {
                s_shape.setPosition(sf::Vector2f(s_shape.getPosition().x, obj.position_y));
            }

            if (obj.size_x != 0.0f) {
                s_shape.setSize(sf::Vector2f(obj.size_x * 50, s_shape.getSize().y));
                s_shape.setTextureRect(sf::IntRect({0,0}, {(int)obj.size_x * 50, 50}));
            }

            map_content.emplace(i, std::move(spikes));
        }
        i++;
    }
}

//
// https://stackoverflow.com/questions/32780046/finding-an-element-in-map-by-its-value
//

auto Map::start(Player& player) -> void {
    if (!level_started) {
        auto start = std::ranges::find_if(map_content, [](auto& pair) {
            return dynamic_cast<Start*>(pair.second.get());
        });

        auto& shape = start->second->getShape();
        player.setPosition(shape.getPosition().x, shape.getPosition().y);
        level_started = true;
    }
}

auto Map::getLevelStarted() -> bool {
    return level_started;
}

auto Map::setLevelStarted(bool value) -> void {
    level_started = value;
}

auto Map::clearMapContent() -> void {
    map_content.clear();
}





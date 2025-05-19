//
// Created by mrlek on 09.05.2025.
//

#ifndef LEVELINTERFACE_H
#define LEVELINTERFACE_H

#include "../entity/Player.h"
#include <SFML/Graphics.hpp>
#include "LevelParser.h"
#include "../utils/Text.h"

class LevelInterface {
private:
    LevelParser::LevelInfo info;

public:
    LevelInterface() = default;

    auto show(sf::RenderWindow &window, Player &player, LevelParser::LevelInfo &info) -> void {
        auto level = info.level;
        auto chapter = info.chapter;
        auto player_data = player.getPlayerData();

        // Chapter and level text
        auto t = Text();
        t.setFontPath("../../assets/fonts/Poppins-SemiBold.ttf");
        auto level_info_text = t.createText();
        level_info_text.setCharacterSize(16);
        level_info_text.setString(fmt::format("Chapter {} - Level {}", chapter, level));
        auto t_bounds = level_info_text.getGlobalBounds();
        level_info_text.setPosition(sf::Vector2f(window.getSize().x - t_bounds.size.x - 25.0f, 25.0f));
        t.renderText(level_info_text, window);

        // Player Info
        auto player_info_text = t.createText();
        player_info_text.setCharacterSize(16);
        player_info_text.setString(fmt::format("{} - LVL : {}", player_data.name, player_data.exp_level));
        auto p_bounds = player_info_text.getGlobalBounds();
        player_info_text.setPosition(sf::Vector2f(25.0f, 25.0f));
        t.renderText(player_info_text, window);

        // Player HP bar
        auto bar = sf::RectangleShape(sf::Vector2f{1.0f, 20.0f});
        bar.scale(sf::Vector2f(player_data.hp, 1));
        bar.setFillColor(sf::Color::Red);
        bar.setPosition(sf::Vector2f(25.0f, 25.0f + p_bounds.size.y + 15.0f));
        window.draw(bar);
    }
};



#endif //LEVELINTERFACE_H

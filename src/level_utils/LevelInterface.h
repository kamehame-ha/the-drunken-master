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
    sf::RenderWindow *window;
    Player *player;
    LevelParser::LevelInfo info;

public:
    LevelInterface(sf::RenderWindow *window, Player *player, LevelParser::LevelInfo &info) {
        this->window = window;
        this->player = player;
        this->info = info;
    }

    auto show() -> void {
        auto hp = player->getHp();
        auto level = info.level;
        auto chapter = info.chapter;

        // Chaper and level text
        auto t = Text(*window);
        t.setFontPath("../../assets/fonts/Poppins-SemiBold.ttf");
        auto level_info_text = t.createText();
        level_info_text.setCharacterSize(16);
        level_info_text.setString("Chapter " + std::to_string(chapter) + " - " + "Level " + std::to_string(level));
        auto t_bounds = level_info_text.getGlobalBounds();
        level_info_text.setPosition(sf::Vector2f(window->getSize().x - t_bounds.size.x - 25.0f, 25.0f));
        t.renderText(level_info_text);

        // Player HP bar
        auto bar = sf::RectangleShape(sf::Vector2f{1.5f, 20.0f});
        bar.scale(sf::Vector2f(hp, 1));
        bar.setFillColor(sf::Color::Red);
        bar.setPosition(sf::Vector2f(25.0f, 25.0f));
        auto bar_text = t.createText();
        bar_text.setCharacterSize(12);
        bar_text.setString(std::to_string(hp));
        bar_text.setPosition(sf::Vector2f(30.0f, 28.0f));
        window->draw(bar);
        t.renderText(bar_text);
    }
};



#endif //LEVELINTERFACE_H

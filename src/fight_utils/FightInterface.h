//
// Created by mrlek on 12.05.2025.
//

#ifndef FIGHTINTERFACE_H
#define FIGHTINTERFACE_H

#include <SFML/Graphics.hpp>

#include "FightState.h"
#include "../entity/Enemy.h"
#include "../entity/Player.h"
#include "../utils/Text.h"


class FightInterface {
private:
    std::vector<std::string> status_log_messages;

public:
    FightInterface() = default;

    enum FightMove {
        WAIT,
        DODGE,
        LIGHT_ATTACK,
        HEAVY_ATTACK,
        NONE
    };

    FightMove chosenMove;

    auto show(
        sf::RenderWindow &window,
        GameSave::PlayerData& player_data,
        Enemy::EnemyData& enemy_data,
        sf::Vector2f mouse_position,
        bool mouse_pressed,
        FightState::State state
        )
    -> void {
        auto t = Text();
        chosenMove = NONE;

        // Enemy info
        sf::RectangleShape enemy_info_box(sf::Vector2f(400.f, 75.f));
        enemy_info_box.setPosition(sf::Vector2f(25.f, 25.f));
        enemy_info_box.setFillColor(sf::Color(36,36,36));

        // Enemy HP bar
        sf::RectangleShape enemy_hp_bar(sf::Vector2f(1.f, 20.f));
        enemy_hp_bar.setPosition(sf::Vector2f(35.f, 70.f));
        enemy_hp_bar.setFillColor(sf::Color::Red);
        enemy_hp_bar.scale(sf::Vector2f(enemy_data.hp, 1.f));

        // Enemy character
        sf::CircleShape enemy_character(100.f);
        enemy_character.setPosition(sf::Vector2f(649.f, 25.f));
        enemy_character.setFillColor(sf::Color::Magenta);


        // Player info
        sf::RectangleShape player_info_box(sf::Vector2f(375.f, 150.f));
        player_info_box.setPosition(sf::Vector2f(624.f, 593.f));
        player_info_box.setFillColor(sf::Color(36,36,36));

        // Player moveset box
        sf::RectangleShape player_moveset_box(sf::Vector2f(574.f, 150.f));
        player_moveset_box.setPosition(sf::Vector2f(25.f, 593.f));
        player_moveset_box.setFillColor(sf::Color(36,36,36));

        // Player HP bar
        sf::RectangleShape player_hp_bar(sf::Vector2f(1.f, 20.f));
        player_hp_bar.setPosition(sf::Vector2f(634.f, 603.f + 26.f + 20.f));
        player_hp_bar.setFillColor(sf::Color::Red);
        player_hp_bar.scale(sf::Vector2f(player_data.hp, 1.f));

        // Player Stamina bar
        sf::RectangleShape player_stamina_bar(sf::Vector2f(1.f, 20.f));
        player_stamina_bar.setPosition(sf::Vector2f(634.f, 603.f + 26.f + 20.f + 20.f + 10.f));
        player_stamina_bar.setFillColor(sf::Color::Green);
        player_stamina_bar.scale(sf::Vector2f(player_data.stamina, 1.f));

        // Player character
        sf::CircleShape player_character(125.f);
        player_character.setPosition(sf::Vector2f(174.5f, 418.f));
        player_character.setFillColor(sf::Color::Blue);

        window.draw(player_character);
        window.draw(player_info_box);
        window.draw(player_moveset_box);
        window.draw(player_hp_bar);
        window.draw(player_stamina_bar);
        window.draw(enemy_info_box);
        window.draw(enemy_character);
        window.draw(enemy_hp_bar);

        // Enemy info text
        t.setFontPath("../../assets/fonts/Poppins-SemiBold.ttf");
        auto enemy_info_text = t.createText();
        enemy_info_text.setCharacterSize(20);
        enemy_info_text.setString(fmt::format("{}", enemy_data.name));
        enemy_info_text.setPosition(sf::Vector2f(35.f, 35.f));

        t.renderText({enemy_info_text}, window);

        ////// Player moveset texts
        t.setFontPath("../../assets/fonts/Poppins-Black.ttf");
        // Light attack
        auto light_attack_text = t.createText();
        light_attack_text.setCharacterSize(32);
        light_attack_text.setString("LIGHT ATTACK");
        light_attack_text.setPosition(sf::Vector2f(45.f, 608.f));

        // Heavy attack
        auto heavy_attack_text = t.createText();
        heavy_attack_text.setCharacterSize(32);
        heavy_attack_text.setString("HEAVY ATTACK");
        heavy_attack_text.setPosition(sf::Vector2f(599.f - heavy_attack_text.getGlobalBounds().size.x - 20.f, 608.f));

        // Dodge
        auto dodge_text = t.createText();
        dodge_text.setCharacterSize(32);
        dodge_text.setString("DODGE");
        dodge_text.setPosition(sf::Vector2f(45.f, 593.f + 150.f - (dodge_text.getGlobalBounds().size.y * 2) - 10.f));

        // Block
        auto wait_text = t.createText();
        wait_text.setCharacterSize(32);
        wait_text.setString("WAIT");
        wait_text.setPosition(sf::Vector2f(heavy_attack_text.getGlobalBounds().position.x, 593.f + 150.f - (wait_text.getGlobalBounds().size.y * 2) - 10.f));

        if (light_attack_text.getGlobalBounds().contains(mouse_position) && state == FightState::PLAYER_TURN) {
            light_attack_text.setFillColor(sf::Color::Red);

            if (mouse_pressed) {
                chosenMove = LIGHT_ATTACK;
            }
        } else if (heavy_attack_text.getGlobalBounds().contains(mouse_position) && state == FightState::PLAYER_TURN) {
            heavy_attack_text.setFillColor(sf::Color::Red);

            if (mouse_pressed) {
                chosenMove = HEAVY_ATTACK;
            }
        } else if (dodge_text.getGlobalBounds().contains(mouse_position) && state == FightState::ENEMY_TURN && player_data.stamina > 25) {
            dodge_text.setFillColor(sf::Color::Red);

            if (mouse_pressed) {
                chosenMove = DODGE;
            }
        } else if (wait_text.getGlobalBounds().contains(mouse_position) && state == FightState::ENEMY_TURN) {
            wait_text.setFillColor(sf::Color::Red);

            if (mouse_pressed) {
                chosenMove = WAIT;
            }
        }

        t.renderText({light_attack_text, heavy_attack_text, dodge_text, wait_text}, window);

        // Player info text
        t.setFontPath("../../assets/fonts/Poppins-SemiBold.ttf");
        auto player_info_text = t.createText();
        player_info_text.setCharacterSize(26);
        player_info_text.setString(fmt::format("{} - LVL : {}", player_data.name, player_data.exp_level));
        player_info_text.setPosition(sf::Vector2f(634.f, 603.f));

        t.renderText(player_info_text, window);
    }

    void statusLogAddMsg(const std::string& msg) {
        status_log_messages.insert(status_log_messages.begin(), msg);
        if (status_log_messages.size() > 5) {
            status_log_messages.pop_back();
        }
    }

    void showStatusLog(sf::RenderWindow &window) {
        auto t = Text();
        t.setFontPath("../../assets/fonts/Poppins-Medium.ttf");
        std::vector<sf::Text> texts;

        if (status_log_messages.empty()) return;

        for (const auto& msg : status_log_messages) {
            auto text = t.createText();
            text.setString(msg);
            text.setCharacterSize(16);
            texts.push_back(text);
        }

        float start_y = 593.f - 25.f;
        float line_height = texts[0].getGlobalBounds().size.y + 5.f;

        for (size_t i = 0; i < texts.size(); ++i) {
            float x = window.getSize().x - texts[i].getGlobalBounds().size.x - 25.f;
            float y = start_y - (texts.size() - i - 1) * line_height;
            texts[i].setPosition({x, y});
        }

        t.renderText(texts, window);  // Use vector version of renderText
    }

    void resetStatusLog() {
        status_log_messages.clear();
    }

    auto chosenAction() -> FightMove {
        return chosenMove;
    }
};



#endif //FIGHTINTERFACE_H

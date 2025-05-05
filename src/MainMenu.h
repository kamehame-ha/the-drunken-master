//
// Created by mrlek on 25.04.2025.
//

#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Game.h"

#include "utils/Delay.h"


class MainMenu {
private:
    std::string title_menu_texture_path;
    std::string title_menu_music_path;
    sf::Texture title_menu_texture;

public:
    sf::Sprite title_menu_sprite = sf::Sprite(title_menu_texture);
    sf::Music title_menu_music = sf::Music();

    explicit MainMenu();
    auto init() -> void;
    auto start(sf::RenderWindow &window, Delay &delay) -> void;
};


#endif //MAINMENU_H

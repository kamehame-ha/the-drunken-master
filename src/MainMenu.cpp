//
// Created by mrlek on 25.04.2025.
//

#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow &window, GameState::State state): window(), state() {
    title_menu_texture_path = "../../assets/textures/drunken-master-game-art.png";
    title_menu_music_path = "../../assets/music/gooffy-ass-pokemon-theme.mp3";
}

auto MainMenu::init() -> void {
    // Load texture first
    if (!title_menu_texture.loadFromFile(title_menu_texture_path)) {
        throw std::runtime_error("Failed to load texture");
    }

    // Then set it to the sprite
    title_menu_sprite = sf::Sprite(title_menu_texture);
    title_menu_sprite.scale({1, 1});

    // Load music
    if (!title_menu_music.openFromFile(title_menu_music_path)) {
        throw std::runtime_error("Error loading music");
    }
}


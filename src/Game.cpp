//
// Created by kame on 4/25/25.
//

#include "Game.h"

#include "Window.h"

//////////// Lifecycle values ////////////

// Those values are grouped using a simple method <some-text>_<number>
// By overwriting any group of values, leaving one true and the rest false
// should allow easy debug/presentation of every aspect of the game.
// Comments after each value is just simple explanation for what moment of
// the lifecycle it is needed

bool main_menu_stage_one = false; // Content such as music and basic sprite is loaded
bool main_menu_stage_two = true; //
bool main_menu_stage_three = false;

//////////// Font paths ////////////

std::string pp_light = "../../assets/fonts/Poppins-Light.ttf";
std::string pp_regular = "../../assets/fonts/Poppins-Regular.ttf";
std::string pp_medium = "../../assets/fonts/Poppins-Medium.ttf";
std::string pp_semi_bold = "../../assets/fonts/Poppins-SemiBold.ttf";
std::string pp_bold = "../../assets/fonts/Poppins-Bold.ttf";
std::string pp_extra_bold = "../../assets/fonts/Poppins-ExtraBold.ttf";
std::string pp_black = "../../assets/fonts/Poppins-Black.ttf";
std::string pp_italic = "../../assets/fonts/Poppins-Italic.ttf";


sf::Music createMusic(const std::string& path) {
    sf::Music music;

    if (!music.openFromFile(path)) {
        throw std::runtime_error("Error loading music");
    }

    return music;
}

sf::Sprite createSprite(sf::Texture& texture, const std::string& path) {
    if (!texture.loadFromFile(path)) {
        throw std::runtime_error("Failed to load texture");
    }

    return sf::Sprite(texture);
}

Game::Game() {
    // Constructor implementation
}

void Game::run() {
    auto windowSize = sf::Vector2u(1024, 768);
    auto window = Window(sf::VideoMode(windowSize), "Drunken Master").create();

    window.setMinimumSize(windowSize);
    window.setMaximumSize(windowSize);

    // Title menu image
    sf::Texture title_menu_texture;
    sf::Sprite title_menu_sprite = createSprite(title_menu_texture,"../../assets/textures/drunken-master-game-art.png");
    title_menu_sprite.scale({1, 1});

    // Title menu music
    sf::Music title_menu_music = createMusic("../../assets/music/gooffy-ass-pokemon-theme.mp3");
    title_menu_music.play();

    // Base clock
    sf::Clock clock;

    // Main while loop, centerpiece of program life
    while (window.isOpen()) {

        // Key/Button/Mouse events
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (auto key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::Enter) {

                }
            }
        }

        // Set default background color
        window.clear(sf::Color(0x121212));

        // Title menu life cycle start
        window.draw(title_menu_sprite);
        main_menu_stage_one = false;

        if (clock.getElapsedTime().asSeconds() > 5) {
            main_menu_stage_two = true;
        }

        if (main_menu_stage_two) {
            window.clear(sf::Color(0x121212));

            auto text_lines = std::vector<std::string>{
                "Keybinds:",
                "Walking - WASD",
                "Jump - Space",
                "Menu navigation - Arrow Keys",
                "Menu Accept - Enter",
                "Menu Back - Backspace",
                "Interaction - E"
            };

            auto text_vector = std::vector<sf::Text>{};

            auto text = Text(window);

            text.setFontPath(pp_regular);
            text.setFont(sf::Font());

            for (const std::string& t : text_lines) {
                auto line = text.createText();
                line.setString(t);
                text_vector.push_back(line);
            }

            text.renderText(text.centerTextLines(text_vector));
        }

        // Display
        window.display();
    }
}
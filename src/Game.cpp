//
// Created by kame on 4/25/25.
//

#include "Game.h"

#include "MainMenu.h"

//////////// Lifecycle values ////////////

// Those values are grouped using a simple method <some-text>_<number>
// By overwriting any group of values, leaving one true and the rest false
// should allow easy debug/presentation of every aspect of the game.
// Comments after each value is just simple explanation for what moment of
// the lifecycle it is needed

bool main_menu_stage_one = true; // Content such as music and basic sprite is loaded
bool main_menu_stage_two = false; //
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

Game::Game() {
    this->windowSize = sf::Vector2u(1024, 768);
}

void Game::run() const {
    Game();
    auto window = Window(sf::VideoMode(windowSize), "Drunken Master").create();
    window.setFramerateLimit(60);

    sf::Image icon;

    if (!icon.loadFromFile("../../assets/textures/logo.png")) {
        throw std::runtime_error("Error loading icon");
    }

    window.setIcon(icon);

    MainMenu main_menu;
    main_menu.init();

    main_menu.title_menu_music.play();

    auto delay = Delay();

    delay.start(5.0f);

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
        main_menu.start(window, delay);

        // Display
        window.display();
    }
}

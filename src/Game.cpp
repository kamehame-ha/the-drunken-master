//
// Created by kame on 4/25/25.
//

#include "Game.h"

#include "MainMenu.h"

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

        if (GameState::state == GameState::State::GAME) {
            // Main Game Loop
        }

        // Display
        window.display();
    }
}

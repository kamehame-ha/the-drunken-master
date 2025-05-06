//
// Created by kame on 4/25/25.
//

#include "Game.h"

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
    windowSize = sf::Vector2u(1024, 768);
}

void Game::run() const {
    Game();

    auto window = Window(sf::VideoMode(windowSize), "Drunken Master").create();
    window.setFramerateLimit(60);

    auto wrapper = Wrapper(window);

    auto player = Player(100, 10, std::string("Player"));
    player.create();
    auto [x,y] = wrapper.center(player.getShape());
    player.getShape().setPosition(sf::Vector2f(x, y));

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

    sf::Clock clock;

    // Main while loop, centerpiece of program life
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        // Key/Button/Mouse events
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (GameState::getState() == GameState::State::GAME) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                    player.move(Player::moveType::LEFT);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                    player.move(Player::moveType::RIGHT);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                    player.move(Player::moveType::UP);
                }
            }
        }

        player.update(deltaTime);

        // Set default background color
        window.clear(sf::Color(0x121212));

        // Title menu life cycle start
        main_menu.start(window, delay);

        if (GameState::getState() == GameState::State::GAME) {
            window.draw(player.getShape());
        }

        // Display
        window.display();
    }
}

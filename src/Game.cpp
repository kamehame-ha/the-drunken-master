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

Game::Game(): map(), hitbox(), player() {
    windowSize = sf::Vector2u(1024, 768);
}

void Game::run() {
    Game();
    bool once = true;

    // Set gamestate to GAME for game logic testing
    GameState::setState(GameState::MAIN_MENU);

    auto window = Window(sf::VideoMode(windowSize), "Drunken Master").create();
    window.setFramerateLimit(60);

    sf::Image icon;

    if (!icon.loadFromFile("../../assets/textures/logo.png")) {
        throw std::runtime_error("Error loading icon");
    }

    window.setIcon(icon);

    MainMenu main_menu;
    main_menu.init();

    if (GameState::getState() == GameState::State::MAIN_MENU) {
        // main_menu.title_menu_music.play();
    }

    auto delay = Delay();
    delay.start(5.0f);

    sf::Clock clock;

    // Main while loop, centerpiece of program life
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        // Set default background color
        window.clear(sf::Color(18,18,18));

        // Title menu life cycle start
        if (GameState::getState() == GameState::State::MAIN_MENU) {
            main_menu.start(window, delay);

            if (once == true) {
                auto name = std::string("ViperFang661");
                auto game_save = GameSave();
                auto player_data = game_save.load(name);

                //
                // https://www.geeksforgeeks.org/smart-pointers-cpp/
                //
                player = std::make_unique<Player>(player_data);
                player->create();
                hitbox = std::make_unique<Hitbox>(window, *player);
                map = std::make_unique<Map>(window, *player);

                once = false;
            }
        }


        if (GameState::getState() == GameState::State::GAME) {
            main_menu.title_menu_music.stop();
            auto player_data = player->getPlayerData();

            if (player_data.current_level < 6) {
                map->generate(player_data.current_chapter, player_data.current_level);
                map->start();
                map->draw();
                window.draw(player->getShape());
                hitbox->resolveGlobalCollision(deltaTime, *map);
            } else {
                fmt::println("Fight!");
            }
        }

        // Key/Button/Mouse events
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Handle key releases
            if (const auto* keyPressed = event->getIf<sf::Event::KeyReleased>()) {
                player->handleInputRelease(keyPressed->code);
            }

            if (GameState::getState() == GameState::State::GAME) {
                // Movement keys - these will set movement flags
                if (isKeyPressed(sf::Keyboard::Key::A)) {
                    player->move(Player::moveType::LEFT);
                }
                else if (isKeyPressed(sf::Keyboard::Key::D)) {
                    player->move(Player::moveType::RIGHT);
                }
                else {
                    // No horizontal keys pressed
                    player->handleInputRelease(sf::Keyboard::Key::A);
                    player->handleInputRelease(sf::Keyboard::Key::D);
                }

                if (isKeyPressed(sf::Keyboard::Key::W) || isKeyPressed(sf::Keyboard::Key::Space)) {
                    player->move(Player::moveType::UP);
                }
            }
        }

        // Display
        window.display();
    }
}

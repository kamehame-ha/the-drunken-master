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

    // Set gamestate to GAME for game logic testing
    GameState::setState(GameState::GAME);

    auto window = Window(sf::VideoMode(windowSize), "Drunken Master").create();
    window.setFramerateLimit(60);

    auto wrapper = Wrapper(window);

    auto name = std::string("test_player");
    auto game_save = GameSave();
    game_save.NewGame(name);
    auto& player_data = game_save.Load(name);

    auto player = Player(player_data);
    player.create();
    auto [x,y] = wrapper.center(player.getShape());
    player.getShape().setPosition(sf::Vector2f(x, y));

    auto hitbox = Hitbox(window, player);

    auto map = Map(window, player);
    map.generate(player_data.current_chapter, player_data.current_level);
    map.start();

    sf::Image icon;

    if (!icon.loadFromFile("../../assets/textures/logo.png")) {
        throw std::runtime_error("Error loading icon");
    }

    window.setIcon(icon);

    MainMenu main_menu;
    main_menu.init();

    if (GameState::getState() == GameState::State::MAIN_MENU) {
        main_menu.title_menu_music.play();
    }

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

            // Handle key releases
            if (const auto* keyPressed = event->getIf<sf::Event::KeyReleased>()) {
                player.handleInputRelease(keyPressed->code);
            }

            if (GameState::getState() == GameState::State::GAME) {
                // Movement keys - these will set movement flags
                if (isKeyPressed(sf::Keyboard::Key::A)) {
                    player.move(Player::moveType::LEFT);
                }
                else if (isKeyPressed(sf::Keyboard::Key::D)) {
                    player.move(Player::moveType::RIGHT);
                }
                else {
                    // No horizontal keys pressed
                    player.handleInputRelease(sf::Keyboard::Key::A);
                    player.handleInputRelease(sf::Keyboard::Key::D);
                }

                if (isKeyPressed(sf::Keyboard::Key::W) || isKeyPressed(sf::Keyboard::Key::Space)) {
                    player.move(Player::moveType::UP);
                }
            }
        }

        // Set default background color
        window.clear(sf::Color(18,18,18));

        // Title menu life cycle start
        if (GameState::getState() == GameState::State::MAIN_MENU) {
            main_menu.start(window, delay);
        }

        if (GameState::getState() == GameState::State::GAME) {
            map.draw();
            window.draw(player.getShape());
            hitbox.resolveGlobalCollision(deltaTime, map);
        }

        // Display
        window.display();
    }
}

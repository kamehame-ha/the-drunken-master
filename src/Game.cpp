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
    auto g_state = GameState(GameState::State::GAME);

    auto window = Window(sf::VideoMode(windowSize), "Drunken Master").create();
    window.setFramerateLimit(60);

    auto wrapper = Wrapper(window);

    auto player = Player(100, 10, std::string("Player"));
    player.create();
    auto [x,y] = wrapper.center(player.getShape());
    player.getShape().setPosition(sf::Vector2f(x, y));

    auto hitbox = Hitbox(window, player);

    sf::Image icon;

    if (!icon.loadFromFile("../../assets/textures/logo.png")) {
        throw std::runtime_error("Error loading icon");
    }

    window.setIcon(icon);

    MainMenu main_menu;
    main_menu.init();

    if (g_state.getState() == GameState::State::MAIN_MENU) {
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

            if (g_state.getState() == GameState::State::GAME) {
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

        player.update(deltaTime);
        hitbox.check();

        // Set default background color
        window.clear(sf::Color(0x121212));

        // Title menu life cycle start
        main_menu.start(window, delay);

        if (g_state.getState() == GameState::State::GAME) {
            window.draw(player.getShape());

            Element el = Element(window, player);
            el.create();

            el.getShape().setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 + 250));
            window.draw(el.getShape());
            el.checkCollision();
        }

        // Display
        window.display();
    }
}

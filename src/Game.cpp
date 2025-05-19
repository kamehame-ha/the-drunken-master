//
// Created by kame on 4/25/25.
//

#include "Game.h"

#include "fight_utils/Fight.h"

//////////// Font paths ////////////

std::string pp_light = "../../assets/fonts/Poppins-Light.ttf";
std::string pp_regular = "../../assets/fonts/Poppins-Regular.ttf";
std::string pp_medium = "../../assets/fonts/Poppins-Medium.ttf";
std::string pp_semi_bold = "../../assets/fonts/Poppins-SemiBold.ttf";
std::string pp_bold = "../../assets/fonts/Poppins-Bold.ttf";
std::string pp_extra_bold = "../../assets/fonts/Poppins-ExtraBold.ttf";
std::string pp_black = "../../assets/fonts/Poppins-Black.ttf";
std::string pp_italic = "../../assets/fonts/Poppins-Italic.ttf";

void Game::run() {
    // env vars
    once = true;
    text_typed = false;
    mouse_pressed = false;
    load_before_fight = true;

    GameState::setState(GameState::MAIN_MENU);
    FightState::setState(FightState::PLAYER_TURN);

    auto window = Window(sf::VideoMode(sf::Vector2u(1024, 768)), "Drunken Master").create();
    window.setFramerateLimit(60);

    sf::Image icon;

    if (!icon.loadFromFile("../../assets/textures/logo.png")) {
        throw std::runtime_error("Error loading icon");
    }

    window.setIcon(icon);

    // Get contents of /saves to a vector

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
        // Mouse
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        mouse_position = sf::Vector2f(mousePos.x, mousePos.y);

        float deltaTime = clock.restart().asSeconds();

        // Key/Button/Mouse events
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Handle key releases
            if (const auto* keyPressed = event->getIf<sf::Event::KeyReleased>()) {
                if (GameState::getState() == GameState::State::GAME) {
                    player->handleInputRelease(keyPressed->code);
                }
            }

            // Mouse click
            if (event->is<sf::Event::MouseButtonPressed>()) {
                mouse_pressed = true;
            }

            if (event->is<sf::Event::MouseButtonReleased>()) {
                mouse_pressed = false;
            }

            if (GameState::getState() == GameState::State::GAME) {
                if (isKeyPressed(sf::Keyboard::Key::A)) {
                    player->move(Player::moveType::LEFT);
                }
                else if (isKeyPressed(sf::Keyboard::Key::D)) {
                    player->move(Player::moveType::RIGHT);
                }
                else {
                    player->handleInputRelease(sf::Keyboard::Key::A);
                    player->handleInputRelease(sf::Keyboard::Key::D);
                }

                if (isKeyPressed(sf::Keyboard::Key::W) || isKeyPressed(sf::Keyboard::Key::Space)) {
                    player->move(Player::moveType::UP);
                }
            }

            if (GameState::getState() == GameState::State::GAME_OVER) {
                if (isKeyPressed(sf::Keyboard::Key::Enter)) {
                    auto game_save = GameSave();
                    data = game_save.load(name);

                    auto temp_player = std::move(player);
                    auto temp_map = std::move(map);
                    auto temp_hitbox = std::move(hitbox);

                    player = std::make_unique<Player>(data);
                    player->create();
                    map = std::make_unique<Map>();
                    hitbox = std::make_unique<Hitbox>();
                    GameState::setState(GameState::State::GAME);
                }
            }

            if (GameState::getState() == GameState::State::FIGHT_WIN) {
                if (isKeyPressed(sf::Keyboard::Key::Enter)) {
                    auto game_save = GameSave();
                    data = game_save.load(name);

                    auto temp_player = std::move(player);
                    auto temp_map = std::move(map);
                    auto temp_hitbox = std::move(hitbox);

                    player = std::make_unique<Player>(data);
                    player->create();
                    map = std::make_unique<Map>();
                    hitbox = std::make_unique<Hitbox>();

                    if (data.current_chapter == 3) {
                        GameState::setState(GameState::State::GAME_END);
                    } else {
                        GameState::setState(GameState::State::GAME);
                    }

                }
            }

            // Text input
            if (GameState::getState() == GameState::State::MAIN_MENU_NEW_GAME || GameState::getState() == GameState::State::MAIN_MENU_LOAD_GAME)
            {
                if (const auto* textEvent = event->getIf<sf::Event::TextEntered>()) {
                    uint32_t unicode = textEvent->unicode;

                    if ((unicode >= 'A' && unicode <= 'Z') ||
                        (unicode >= 'a' && unicode <= 'z') ||
                        (unicode >= '0' && unicode <= '9'))
                    {
                        if (name.size() < 20) {
                            name += static_cast<char>(unicode);
                        }
                    }
                }

                if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                    if (keyPressed->code == sf::Keyboard::Key::Backspace) {
                        if (!name.empty()) {
                            name.pop_back();
                        }
                    }
                    else if (keyPressed->code == sf::Keyboard::Key::Enter) {
                        text_typed = true;
                    }
                }
            }
        }

        window.clear(sf::Color(18,18,18));

        // Title menu life cycle start
        if (GameState::getState() == GameState::State::MAIN_MENU) {
            main_menu.start(window, delay);
        }

        if (GameState::getState() == GameState::State::MAIN_MENU_SELECT) {
            auto t = Text();
            t.setFontPath(pp_semi_bold);

            auto new_game_text = t.createText();
            new_game_text.setCharacterSize(36);
            new_game_text.setString("New Game");
            auto new_bounds = new_game_text.getGlobalBounds();

            auto load_game_text = t.createText();
            load_game_text.setCharacterSize(36);
            load_game_text.setString("Load Game");
            auto load_bounds = load_game_text.getGlobalBounds();

            // Calculate vertical positioning
            auto spacing = 40.f;  // Space between menu items
            auto total_height = new_bounds.size.y + load_bounds.size.y + spacing;
            auto start_y = (window.getSize().y - total_height) / 2;

            new_game_text.setPosition(sf::Vector2f(
                (window.getSize().x / 2) - (new_bounds.size.x / 2),
                start_y
            ));

            load_game_text.setPosition(sf::Vector2f(
                (window.getSize().x / 2) - (load_bounds.size.x / 2),
                start_y + new_bounds.size.y + spacing
            ));

            if (new_game_text.getGlobalBounds().contains(mouse_position)) {
                new_game_text.setFillColor(sf::Color::Red);

                if (mouse_pressed) {
                    GameState::setState(GameState::State::MAIN_MENU_NEW_GAME);
                }
            }

            if (load_game_text.getGlobalBounds().contains(mouse_position)) {
                load_game_text.setFillColor(sf::Color::Red);

                if (mouse_pressed) {
                    GameState::setState(GameState::State::MAIN_MENU_LOAD_GAME);
                }
            }

            t.renderText(new_game_text, window);
            t.renderText(load_game_text, window);
        }

        if (GameState::getState() == GameState::State::MAIN_MENU_NEW_GAME) {
            auto t = Text();
            t.setFontPath(pp_semi_bold);
            auto save_name_text = t.createText();
            save_name_text.setCharacterSize(32);
            save_name_text.setString(fmt::format("New save name: {}", name));
            auto st_bounds = save_name_text.getGlobalBounds();
            save_name_text.setPosition(sf::Vector2f((window.getSize().x / 2) - (st_bounds.size.x / 2), (window.getSize().y / 2) - (st_bounds.size.y / 2)));
            t.renderText(save_name_text, window);

            if (text_typed) {
                auto game_save = GameSave();
                game_save.newGame(name);
                save_typed_or_selected = true;
                GameState::setState(GameState::State::GAME);
            }
        }

        if (GameState::getState() == GameState::State::MAIN_MENU_LOAD_GAME) {
            auto t = Text();
            t.setFontPath(pp_semi_bold);
            auto save_name_text = t.createText();
            save_name_text.setCharacterSize(32);
            save_name_text.setString(fmt::format("Save name: {}", name));
            auto st_bounds = save_name_text.getGlobalBounds();
            save_name_text.setPosition(sf::Vector2f((window.getSize().x / 2) - (st_bounds.size.x / 2), (window.getSize().y / 2) - (st_bounds.size.y / 2)));
            t.renderText(save_name_text, window);

            if (text_typed) {
                std::ifstream file("../../saves/" + name + ".txt");
                if (file.good()) {
                    save_typed_or_selected = true;
                    GameState::setState(GameState::State::GAME);
                } else {
                    fmt::print("This save file does not exist, going back to selection menu\n");
                    text_typed = false;
                    save_typed_or_selected = false;
                    name = "";
                    GameState::setState(GameState::State::MAIN_MENU_SELECT);
                }
            }
        }

        if (once == true && save_typed_or_selected == true) {
            auto game_save = GameSave();
            data = game_save.load(name);

            //
            // https://www.geeksforgeeks.org/smart-pointers-cpp/
            //
            player = std::make_unique<Player>(data);
            player->create();
            map = std::make_unique<Map>();
            hitbox = std::make_unique<Hitbox>();

            auto enemy = Enemy();
            enemy_data = enemy.create(player->getPlayerData().exp_level);

            once = false;
        }

        if (GameState::getState() == GameState::State::GAME) {
            load_before_fight = true;
            main_menu.title_menu_music.stop();
            auto player_data = player->getPlayerData();

            if (player_data.current_level < 6) {
                map->generate(player_data.current_chapter, player_data.current_level, window, *player);
                map->start(*player);
                map->draw(window, *player);
                window.draw(player->getShape());
                hitbox->resolveGlobalCollision(deltaTime, *map, window, *player);

                if (player_data.hp == 0) {
                    GameState::setState(GameState::State::GAME_OVER);
                    player_data.hp = player_data.max_hp;

                    auto game_save = GameSave();
                    game_save.save(player_data);

                    map->clearMapContent();
                }

                if (!map->getLevelStarted()) {
                    auto game_save = GameSave();
                    //
                    // // Handle items, exp etc.
                    player_data.current_level++;
                    // // Auto save
                    game_save.save(player_data);
                    // // Update player data for UI
                    player->setPlayerData(player_data);

                    map->clearMapContent();
                }
            } else {
                map->clearMapContent();
                GameState::setState(GameState::State::FIGHT);
            }
        }

        if (GameState::getState() == GameState::State::FIGHT) {
            auto fight = Fight();

            if (load_before_fight == true) {
                auto game_save = GameSave();
                data = game_save.load(name);
                enemy_data = Enemy().create(data.exp_level);
                load_before_fight = false;
            }

            fight_interface.show(window, data, enemy_data, mouse_position, mouse_pressed, FightState::getState());
            fight_interface.showStatusLog(window);

            // Auto set enemy turn if player has no stamina
            if (data.stamina < 25 && FightState::getState() == FightState::PLAYER_TURN) {
                fight_interface.statusLogAddMsg("Not enough stamina to attack, use WAIT in you next turn");
                FightState::setState(FightState::ENEMY_TURN);
            }

            if (FightState::getState() == FightState::PLAYER_TURN) {
                auto chosenAction = fight_interface.chosenAction();
                if (chosenAction == FightInterface::LIGHT_ATTACK) {
                    auto l_attack = fight.lightAttack(data, enemy_data, FightState::getState());
                    enemy_data.hp = enemy_data.hp - l_attack;
                    std::string l_msg = l_attack != 0 ? fmt::format("Player used light attack, dealing {}dmg", l_attack) : "Player missed";
                    fight_interface.statusLogAddMsg(l_msg);
                    FightState::setState(FightState::ENEMY_TURN);
                } else if (chosenAction == FightInterface::HEAVY_ATTACK) {
                    auto h_attack = fight.heavyAttack(data, enemy_data, FightState::getState());
                    enemy_data.hp = enemy_data.hp - h_attack;
                    std::string h_msg = h_attack != 0 ? fmt::format("Player used heavy attack, dealing {}dmg", h_attack) : "Player missed";
                    fight_interface.statusLogAddMsg(h_msg);
                    FightState::setState(FightState::ENEMY_TURN);
                }
            }

            if (FightState::getState() == FightState::ENEMY_TURN) {
                // 0 - light attack
                // 1 - heavy attack
                auto move = Dice(1).roll();
                auto dmg = move > 0 ? fight.heavyAttack(data, enemy_data, FightState::getState()) : fight.lightAttack(data, enemy_data, FightState::getState());

                auto chosenAction = fight_interface.chosenAction();
                if (chosenAction == FightInterface::DODGE) {
                    auto d_msg = dmg != 0 ? fmt::format("Enemy used {} attack dealing {}dmg",
                                      move > 0 ? "heavy attack" : "light attack", dmg) : "Enemy missed";

                    if (fight.dodge(player->getPlayerData())) {
                        d_msg = "Player dodged incoming attack";
                        data.stamina = data.stamina - Dice(15).roll();
                        fight_interface.statusLogAddMsg(d_msg);
                    } else {
                        data.stamina = data.stamina - 25;
                        data.hp = data.hp - dmg;
                        fight_interface.statusLogAddMsg(d_msg);
                    }

                    FightState::setState(FightState::PLAYER_TURN);
                } else if (chosenAction == FightInterface::WAIT) {
                    auto b_msg = dmg != 0 ? fmt::format("Enemy used {} attack dealing {}dmg",
                                      move > 0 ? "heavy attack" : "light attack", dmg) : "Enemy missed";

                    data.hp = data.hp - dmg;
                    auto bonus_stamina = Dice(25).roll();
                    data.stamina = data.stamina + bonus_stamina;
                    if (data.stamina > 100) data.stamina = 100;
                    fight_interface.statusLogAddMsg(fmt::format("{}, you got {} stamina", b_msg, bonus_stamina));

                    FightState::setState(FightState::PLAYER_TURN);
                }
            }

            if (enemy_data.hp < 0) {
                data.hp = data.max_hp;
                data.stamina = 100;
                data.current_level = 1;
                data.current_chapter += 1;
                player->setPlayerData(data);
                auto game_save = GameSave();
                game_save.save(data);
                fight_interface.resetStatusLog();
                GameState::setState(GameState::FIGHT_WIN);
            }

            if (data.hp < 0) {
                data.hp = data.max_hp;
                data.stamina = 100;
                data.current_level = 1;
                player->setPlayerData(data);
                auto game_save = GameSave();
                game_save.save(data);
                fight_interface.resetStatusLog();
                GameState::setState(GameState::GAME_OVER);
            }
        }

        if (GameState::getState() == GameState::State::GAME_OVER) {
            auto t = Text();
            t.setFontPath(pp_semi_bold);
            auto game_over_text = t.createText();
            game_over_text.setCharacterSize(64);
            game_over_text.setString(fmt::format("Game Over"));
            auto t_bounds = game_over_text.getGlobalBounds();
            game_over_text.setPosition(sf::Vector2f((window.getSize().x / 2) - (t_bounds.size.x / 2), (window.getSize().y / 2) - (t_bounds.size.y / 2)));
            t.renderText(game_over_text, window);

            t.setFontPath(pp_light);
            auto game_over_sub_text = t.createText();
            game_over_sub_text.setCharacterSize(18);
            game_over_sub_text.setString(fmt::format("Press Enter to continue"));
            auto ts_bounds = game_over_sub_text.getGlobalBounds();
            game_over_sub_text.setPosition(sf::Vector2f((window.getSize().x / 2) - (ts_bounds.size.x / 2), (window.getSize().y / 2) + (t_bounds.size.y + 15.f)));
            t.renderText(game_over_sub_text, window);
        }

        if (GameState::getState() == GameState::State::FIGHT_WIN) {
            window.clear(sf::Color(18,18,18));

            auto t = Text();
            t.setFontPath(pp_semi_bold);
            auto win_text = t.createText();
            win_text.setCharacterSize(64);
            win_text.setString(fmt::format("You won!"));
            auto t_bounds = win_text.getGlobalBounds();
            win_text.setPosition(sf::Vector2f((window.getSize().x / 2) - (t_bounds.size.x / 2), (window.getSize().y / 2) - (t_bounds.size.y / 2)));
            t.renderText(win_text, window);

            t.setFontPath(pp_light);
            auto win_sub_text = t.createText();
            win_sub_text.setCharacterSize(18);
            win_sub_text.setString(fmt::format("Press Enter to continue"));
            auto ts_bounds = win_sub_text.getGlobalBounds();
            win_sub_text.setPosition(sf::Vector2f((window.getSize().x / 2) - (ts_bounds.size.x / 2), (window.getSize().y / 2) + (t_bounds.size.y + 15.f)));
            t.renderText(win_sub_text, window);
        }

        // if (GameState::getState() == GameState::State::LEVEL_UP) {
        //     auto t = Text();
        //     t.setFontPath(pp_semi_bold);
        //
        //     auto lvl_up_hp_text = t.createText();
        //     lvl_up_hp_text.setCharacterSize(36);
        //     lvl_up_hp_text.setString("Increase HP");
        //     auto new_bounds = lvl_up_hp_text.getGlobalBounds();
        //
        //     auto lvl_up_ad_text = t.createText();
        //     lvl_up_ad_text.setCharacterSize(36);
        //     lvl_up_ad_text.setString("Increase AD");
        //     auto load_bounds = lvl_up_ad_text.getGlobalBounds();
        //
        //     // Calculate vertical positioning
        //     auto spacing = 40.f;  // Space between menu items
        //     auto total_height = new_bounds.size.y + load_bounds.size.y + spacing;
        //     auto start_y = (window.getSize().y - total_height) / 2;
        //
        //     lvl_up_hp_text.setPosition(sf::Vector2f(
        //         (window.getSize().x / 2) - (new_bounds.size.x / 2),
        //         start_y
        //     ));
        //
        //     lvl_up_ad_text.setPosition(sf::Vector2f(
        //         (window.getSize().x / 2) - (load_bounds.size.x / 2),
        //         start_y + new_bounds.size.y + spacing
        //     ));
        //
        //     auto player_data = player->getPlayerData();
        //
        //     if (lvl_up_hp_text.getGlobalBounds().contains(mouse_position)) {
        //         lvl_up_hp_text.setFillColor(sf::Color::Red);
        //
        //         if (mouse_pressed) {
        //             player_data.max_hp += 50;
        //             player_data.hp = player_data.max_hp;
        //             player->setPlayerData(player_data);
        //
        //             auto game_save = GameSave();
        //             game_save.save(player->getPlayerData());
        //
        //             GameState::setState(GameState::State::GAME);
        //         }
        //     }
        //
        //     if (lvl_up_ad_text.getGlobalBounds().contains(mouse_position)) {
        //         lvl_up_ad_text.setFillColor(sf::Color::Red);
        //
        //         if (mouse_pressed) {
        //             player_data.ad += 10;
        //             player->setPlayerData(player_data);
        //
        //             auto game_save = GameSave();
        //             game_save.save(player->getPlayerData());
        //
        //             GameState::setState(GameState::State::GAME);
        //         }
        //     }
        // }

        if (GameState::getState() == GameState::State::GAME_END) {
            window.clear(sf::Color(18,18,18));

            auto t = Text();
            t.setFontPath(pp_semi_bold);
            auto win_text = t.createText();
            win_text.setCharacterSize(64);
            win_text.setString(fmt::format("Thanks for playing"));
            auto t_bounds = win_text.getGlobalBounds();
            win_text.setPosition(sf::Vector2f((window.getSize().x / 2) - (t_bounds.size.x / 2), (window.getSize().y / 2) - (t_bounds.size.y / 2)));
            t.renderText(win_text, window);

            t.setFontPath(pp_light);
            auto win_sub_text = t.createText();
            win_sub_text.setCharacterSize(18);
            win_sub_text.setString(fmt::format("You can close the window"));
            auto ts_bounds = win_sub_text.getGlobalBounds();
            win_sub_text.setPosition(sf::Vector2f((window.getSize().x / 2) - (ts_bounds.size.x / 2), (window.getSize().y / 2) + (t_bounds.size.y + 15.f)));
            t.renderText(win_sub_text, window);
        }
        // Display
        window.display();
    }
}

//
// Created by kame on 4/25/25.
//

#ifndef GAME_H
#define GAME_H

#include "utils/Wrapper.h"
#include "utils/Text.h"
#include "utils/Window.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <fmt/base.h>
#include "fmt/format.h"
#include <iostream>
#include <vector>
#include <string>
#include "utils/GameState.h"
#include "game_utils/MainMenu.h"
#include "entity/Player.h"
#include "map_utils/Hitbox.h"
#include "map_utils/map_elements/Element.h"
#include "map_utils/Map.h"
#include "level_utils/LevelParser.h"
#include "save_utils/GameSave.h"

class Game {
private:
    sf::Vector2u windowSize;
    //
    // https://www.geeksforgeeks.org/smart-pointers-cpp/
    //
    std::unique_ptr<Map> map;
    std::unique_ptr<Hitbox> hitbox;
    std::unique_ptr<Player> player;

public:
    Game();
    auto run() -> void;
};



#endif //GAME_H

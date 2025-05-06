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
#include "MainMenu.h"
#include "Player.h"
#include "map_utils/Hitbox.h"
#include "map_utils/Element.h"

class Game {
private:
    sf::Vector2u windowSize;

public:
    Game();
    auto run() const -> void;
};



#endif //GAME_H

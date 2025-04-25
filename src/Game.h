//
// Created by kame on 4/25/25.
//

#ifndef GAME_H
#define GAME_H

#include "utils/Wrapper.h"
#include "utils/Text.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <fmt/base.h>
#include "fmt/format.h"
#include <iostream>
#include <vector>
#include <string>

class Game {
public:
    Game();
    auto run() -> void;
};



#endif //GAME_H

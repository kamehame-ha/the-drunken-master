//
// Created by mrlek on 10.05.2025.
//

#ifndef GAMESAVE_H
#define GAMESAVE_H

#include <string>
#include <vector>
#include <fmt/base.h>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <string>
#include <cstdlib>
#include "../game_utils/Dice.h"

class GameSave {
public:
    struct PlayerData {
        int hp;
        int ad;
        float move_speed;
        std::string name;
        int exp_level;
        int exp;
        int current_chapter;
        int current_level;
    };

    GameSave();

    auto save(PlayerData& data) -> void;
    auto load(const std::string& name) -> PlayerData&;
    auto newGame() -> void;

private:
    auto trimmer(const std::string& s) -> std::string;
    auto nameGenerator() -> std::string;
    PlayerData player_data;
};

#endif // GAMESAVE_H

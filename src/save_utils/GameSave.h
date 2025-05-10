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

    auto Save(const PlayerData& data) -> void;
    auto Load(const std::string& name) -> PlayerData&;
    auto NewGame(std::string name) -> void;

private:
    auto trimmer(const std::string& s) -> std::string;
    PlayerData player_data;
};

#endif // GAMESAVE_H

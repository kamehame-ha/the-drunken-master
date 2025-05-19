//
// Created by mrlek on 12.05.2025.
//

#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <vector>
#include <fmt/base.h>
#include "../game_utils/Dice.h"


class Enemy {
public:
    struct EnemyData {
        int hp;
        int max_hp;
        int ad;
        std::string name;
    };

    auto create(int player_level) -> EnemyData {
        auto enemy_ad = 10 + (Dice(5).roll() * player_level);
        auto enemy_hp = 100 * player_level + Dice(50).roll();
        auto name_prefix_i = Dice(prefixes.size()).roll();
        auto name_suffix_i = Dice(suffixes.size()).roll();

        return {
            .hp = enemy_hp,
            .max_hp = enemy_hp,
            .ad = enemy_ad,
            .name = fmt::format("{} {}", prefixes[name_prefix_i], suffixes[name_suffix_i]),
        };
    }

private:
    std::vector<std::string> prefixes = {"Monk", "Thug", "Warrior", "Homeless"};
    std::vector<std::string> suffixes = {"Ban", "Kirito", "Ainz Own Goal", "Saitama"};
};



#endif //ENEMY_H

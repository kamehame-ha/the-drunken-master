//
// Created by mrlek on 12.05.2025.
//

#include "Fight.h"

Fight::Fight() = default;

auto Fight::lightAttack(GameSave::PlayerData player_data, Enemy::EnemyData enemy_data, FightState::State state) -> int {
    if (state == FightState::PLAYER_TURN) {
        auto dmg = player_data.ad + Dice(player_data.exp_level * 5).roll();
        // kind of 75% chance
        auto success = Dice(100).roll() > 25;

        return success ? dmg : 0;
    }

    // since enemy ad is already calculated based on player level there's no need to add it here
    auto dmg = enemy_data.ad + Dice(5).roll();
    auto success = Dice(100).roll() > 25;
    return success ? dmg : 0;
}

auto Fight::heavyAttack(GameSave::PlayerData player_data, Enemy::EnemyData enemy_data, FightState::State state) -> int {
    if (state == FightState::PLAYER_TURN) {
        auto dmg = player_data.ad + Dice(player_data.exp_level * 10).roll();
        // 50% chance unless player stamina is below 50
        auto success = player_data.stamina < 50 ? Dice(100).roll() > 75 : Dice(100).roll() > 50;

        return success ? dmg : 0;
    }

    auto dmg = enemy_data.ad + Dice(10).roll();
    auto success = Dice(100).roll() > 50;
    return success ? dmg : 0;
}

auto Fight::dodge(GameSave::PlayerData player_data) -> bool {
    // 50% chance unless player stamina is below 50
    return player_data.stamina < 50 ? Dice(100).roll() > 75 : Dice(100).roll() > 50;
}





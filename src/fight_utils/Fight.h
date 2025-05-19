//
// Created by mrlek on 12.05.2025.
//

#ifndef FIGHT_H
#define FIGHT_H
#include "FightState.h"
#include "../entity/Enemy.h"
#include "../save_utils/GameSave.h"
#include "../game_utils/Dice.h"


class Fight {
public:
    Fight();

    auto lightAttack(GameSave::PlayerData player_data, Enemy::EnemyData enemy_data, FightState::State state) -> int;
    auto heavyAttack(GameSave::PlayerData player_data, Enemy::EnemyData enemy_data, FightState::State state) -> int;

    auto dodge(GameSave::PlayerData player_data) -> bool;
};



#endif //FIGHT_H

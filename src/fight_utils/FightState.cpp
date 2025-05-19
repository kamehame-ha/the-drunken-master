//
// Created by mrlek on 18.05.2025.
//

#include "FightState.h"

FightState::State FightState::state;

auto FightState::getState() -> State {
    return state;
}

auto FightState::setState(State newState) -> void {
    state = newState;
}

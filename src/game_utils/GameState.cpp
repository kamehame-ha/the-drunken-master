//
// Created by mrlek on 25.04.2025.
//

#include "GameState.h"

GameState::State GameState::state;

auto GameState::getState() -> State {
    return state;
}

auto GameState::setState(State newState) -> void {
    state = newState;
}

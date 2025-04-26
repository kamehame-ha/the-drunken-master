//
// Created by mrlek on 25.04.2025.
//

#include "GameState.h"

GameState::State GameState::state;

GameState::GameState(State state) {
    GameState::state = state;
}


auto GameState::getState() -> State {
    return state;
}

auto GameState::setState(State newState) -> void {
    state = newState;
}

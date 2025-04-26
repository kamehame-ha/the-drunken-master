//
// Created by mrlek on 25.04.2025.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H


class GameState {
public:
    enum State {
        MAIN_MENU,
        MAIN_MENU_SELECT
    };

    static State state;

    explicit GameState(State state);

    auto static setState(State state) -> void;
    auto static getState() -> State;
};



#endif //GAMESTATE_H

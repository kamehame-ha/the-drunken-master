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
    auto static setState(State state) -> void;
    auto static getState() -> State;

private:
    static State &state;
};



#endif //GAMESTATE_H

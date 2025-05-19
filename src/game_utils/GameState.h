//
// Created by mrlek on 25.04.2025.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H


class GameState {
public:
    enum State {
        MAIN_MENU,
        MAIN_MENU_SELECT,
        MAIN_MENU_NEW_GAME,
        MAIN_MENU_LOAD_GAME,
        GAME,
        FIGHT,
        GAME_OVER,
        GAME_END,
        LEVEL_UP,
        FIGHT_WIN
    };
    auto static setState(State newState) -> void;
    auto static getState() -> State;

private:
    static State state;
};



#endif //GAMESTATE_H

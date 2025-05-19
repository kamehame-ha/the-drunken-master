//
// Created by mrlek on 18.05.2025.
//

#ifndef FIGHTSTATE_H
#define FIGHTSTATE_H



class FightState {
public:
    enum State {
        PLAYER_TURN,
        ENEMY_TURN
    };
    auto static setState(State newState) -> void;
    auto static getState() -> State;
private:
    static State state;
};



#endif //FIGHTSTATE_H

//
// Created by mrlek on 25.04.2025.
//

#ifndef DELAY_H
#define DELAY_H

#include <SFML/System.hpp>

class Delay {
private:
    sf::Clock clock;
    float duration;
    bool active;

public:
    Delay() : duration(0.0f), active(false) {
        this->clock = sf::Clock();
    };

    void start(const float seconds) {
        duration = seconds;
        active = true;
        clock.restart();
    }

    void stop() {
        active = false;
        clock.stop();
    }
    void cancel() {
        active = false;
    }

    void restart() {
        active = false;
        clock.restart();
    }

    bool isActive() const {
        return active;
    }

    bool isDone() const {
        if (!active) return true;
        return clock.getElapsedTime().asSeconds() >= duration;
    }

};



#endif //DELAY_H

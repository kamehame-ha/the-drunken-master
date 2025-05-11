//
// Created by mrlek on 11.05.2025.
//

#ifndef DICE_H
#define DICE_H

#include <ctime>
#include "random"
#include <fmt/core.h>

//
// https://stackoverflow.com/questions/34126262/use-random-in-a-c-class
//

class Dice {
private:
    std::random_device rd;
    int max_roll = 0;
    std::mt19937 rng;
    std::uniform_int_distribution<> dice;
public:
    explicit Dice(const int mr) : max_roll(mr), rng(rd()), dice(std::uniform_int_distribution<>(1, mr - 1)){
        rng.seed(::time(nullptr));
    }

    int roll() {
        return dice(rng);
    }
};



#endif //DICE_H

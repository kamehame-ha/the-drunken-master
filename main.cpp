#include "src/Game.h"
#include <fmt/base.h>

int main() {
    try {
        const Game game;
        game.run();
    } catch (...) {
        fmt::print(stderr, "Exception occurred\n");
    }
}
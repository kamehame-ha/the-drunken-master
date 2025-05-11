#include "src/Game.h"
#include <fmt/base.h>

int main() {
    try {
        Game game;
        game.run();
    } catch (...) {
        fmt::print(stderr, "Exception occurred\n");
    }
}
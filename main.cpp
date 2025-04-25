#include "src/Game.h"
#include <fmt/base.h>

int main() {
    try {
        auto game = Game();
        game.run();
    } catch (...) {
        fmt::print(stderr, "Exception occurred\n");
    }
}
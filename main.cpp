#include "src/Game.h"
#include <fmt/core.h>
#include <exception>

int main() {
    try {
        Game game;
        game.run();
    } catch (const std::exception& e) {
        fmt::print(stderr, "Standard exception caught: {}\n", e.what());
        return 1;
    } catch (...) {
        fmt::print(stderr, "Unknown exception caught\n");
        return 1;
    }
}

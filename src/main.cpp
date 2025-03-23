#include "core/game.h"

int main(int, char**) {
    auto& game = Game::getInstance();
    game.init("GhostEscape", 1280, 720);
    game.run();
    return 0;
}
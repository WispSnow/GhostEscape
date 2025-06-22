#include "core/game.h"
#include <SDL3/SDL_main.h>

int main(int, char**) {
    auto& game = Game::GetInstance();
    game.init("GhostEscape", 1280, 720);
    game.run();
    return 0;
}
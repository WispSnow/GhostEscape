#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */

#include "core/game.h"
#include <SDL3/SDL_main.h>

/* 此函数在启动时运行一次。 */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    Game::getInstance().init("GhostEscape", 1280, 720);
    return SDL_APP_CONTINUE;
}

/* 此函数在发生新事件（鼠标输入、按键等）时运行。 */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT || Game::getInstance().getIsRunning() == false){
        return SDL_APP_SUCCESS;
    }
    Game::getInstance().handleEvents(*event);
    return SDL_APP_CONTINUE;
}

/* 此函数每帧运行一次，是程序的核心。 */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    static double dt = 0.0;
    static Uint64 frame_delay = static_cast<Uint64>(1000000000.0 / 60.0);
    auto start_time = SDL_GetTicksNS();

    Game::getInstance().update(dt);
    Game::getInstance().render();

    auto end_time = SDL_GetTicksNS();
    auto elapsed_time = end_time - start_time;
    if (elapsed_time < frame_delay) {
        SDL_DelayNS(frame_delay - elapsed_time);
        dt = frame_delay / 1000000000.0;
    }else {
        dt = elapsed_time / 1000000000.0;
    }
    return SDL_APP_CONTINUE;
}

/* 此函数在程序关闭时运行一次。 */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    Game::getInstance().clean();
}

// int main(int, char**) {
//     auto& game = Game::getInstance();
//     game.init("GhostEscape", 1280, 720);
//     game.run();
//     return 0;
// }
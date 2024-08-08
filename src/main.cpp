#include "../include/Scene.hpp"
#include "../include/components.hpp"
#include "../include/ComponentId.hpp"
#include "../include/Ecs.hpp"
#include <cstdlib>


void exit_game() {
    pk::gTexturePool.clear();
    CloseWindow();
}


int main(int argc, char const *argv[]) {
    std::atexit(exit_game);

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(pk::SCREEN_W, pk::SCREEN_H, pk::WINDOW_TITLE);

    pk::gEcs.init();
    pk::gSceneManager.init();
    while (WindowShouldClose() == false) {
        pk::gSceneManager.update(GetFrameTime());
        BeginDrawing();
        ClearBackground(BLACK);
        pk::gSceneManager.draw();
        EndDrawing();
    }    

    return EXIT_SUCCESS;
}

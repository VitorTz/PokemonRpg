//
// Created by vitor on 9/30/24.
//
#include "scene/Scene.h"
#include "util/TexturePool.h"


int main() {
    InitWindow(pk::SCREEN_W, pk::SCREEN_H, pk::WINDOW_TITLE);
    SetTargetFPS(60);

    pk::gSceneManager.init();

    while (WindowShouldClose() == false) {
        pk::gSceneManager.update(GetFrameTime());
        BeginDrawing();
        ClearBackground(BLACK);
        pk::gSceneManager.draw();
        EndDrawing();
    }

    pk::gTexturePool.clear();
    CloseWindow();
    return 0;
}

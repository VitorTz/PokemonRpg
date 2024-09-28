//
// Created by vitor on 9/28/24.
//
#include <raylib.h>
#include "ecs/ECS.h"
#include "scene/Scene.h"
#include "util/constants.h"
#include "util/TexturePool.h"


static void mainloop() {
    pk::gSceneManager.update(GetFrameTime());
    pk::gSceneManager.draw();
}


int main(int argc, char *argv[]) {
    InitWindow(static_cast<int>(pk::SCREEN_W), static_cast<int>(pk::SCREEN_H), pk::WINDOW_TITLE);

    pk::gEcs.init();
    pk::gSceneManager.init();

    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(mainloop, 60, 1);
    #else
        SetTargetFPS(60);
        while (WindowShouldClose() == false) {
            mainloop();
        }
    #endif

    pk::gTexturePool.clear();
    CloseWindow();
    return 0;
}

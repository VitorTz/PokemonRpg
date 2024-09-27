#include <raylib.h>
#include <cassert>
#include "util/constants.hpp"
#include "util/globals.hpp"
#include "ecs/ECS.hpp"



static void mainloop() {    
    // update
        const float dt = GetFrameTime();
        pk::gSceneManager.update(dt);
    // Draw
    pk::gCamera.beginDrawing();
    // BeginDrawing();        
        pk::gSceneManager.draw();
    // EndDrawing();
    pk::gCamera.endDrawing();
}


int main() {
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

    pk::gAssetPool.clear();
    CloseWindow();
    return 0;
}
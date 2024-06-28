#include "include/scene_manager.h"
#include "include/component.h"
#include "include/texture_pool.h"
#include "include/ecs.h"


int main() {
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(POKE_SCREEN_WIDTH, POKE_SCREEN_HEIGHT, POKE_WINDOW_TITLE);
	Image icon = LoadImage(ASSETS_PATH "icon/icon.png");
	SetWindowIcon(icon);	

	poke::gEcs.init();

	poke::gSceneManager.init();
	while (!WindowShouldClose()) {
		poke::gSceneManager.update();
		poke::gSceneManager.draw();
	}


	poke::gTexturePool.clear();
	UnloadImage(icon);
	CloseWindow();

	return 0;
}

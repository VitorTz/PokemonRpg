#include "../include/scene.h"
#include "../include/ecs.h"
#include "../include/scene_manager.h"


poke::TitleScreen::TitleScreen() {

}


void poke::TitleScreen::update() {
	const float dt = GetFrameTime();
	if (IsKeyPressed(KEY_SPACE)) {
		poke::gSceneManager.changeScene(poke::LevelScreenId);
	}
}


void poke::TitleScreen::draw() {
	BeginDrawing();
	ClearBackground(BLACK);	
	EndDrawing();
}
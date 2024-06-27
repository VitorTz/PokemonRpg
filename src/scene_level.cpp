#include "../include/scene.h"


poke::LevelScreen::LevelScreen() {

}


void poke::LevelScreen::update() {
	const float dt = GetFrameTime();
}


void poke::LevelScreen::draw() {
	BeginDrawing();
	ClearBackground(BLACK);
	EndDrawing();
}
#include "../include/scene.h"
#include "../include/ecs.h"
#include "../include/scene_manager.h"


poke::TitleScreen::TitleScreen() {

}


void poke::TitleScreen::update() {
	const float dt = GetFrameTime();	
}


void poke::TitleScreen::draw() {
	BeginDrawing();
	ClearBackground(BLACK);	
	EndDrawing();
}
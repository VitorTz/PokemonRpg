#include "../include/scene.h"


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
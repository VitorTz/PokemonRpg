#include "../include/scene.h"
#include "../include/ecs.h"


poke::LevelScreen::LevelScreen() {
	poke::gPlayer.playerEntity = poke::gEcs.entityCreate(1, true);
	poke::gEcs.addComponent<poke::sprite_t>(poke::gPlayer.playerEntity, poke::sprite_t{ ASSETS_PATH "icon/icon.png" });
	poke::gEcs.addComponent<poke::rigid_body_t>(poke::gPlayer.playerEntity, poke::rigid_body_t{ .speed = POKE_PLAYER_MOVEMENT_SPEED });
	poke::gEcs.addToSystem<poke::player_t>(poke::gPlayer.playerEntity);
}


void poke::LevelScreen::update() {
	const float dt = GetFrameTime();
	poke::gEcs.update(dt);
}


void poke::LevelScreen::draw() {
	BeginDrawing();
	ClearBackground(BLACK);
	poke::gEcs.draw();
	EndDrawing();
}
#include "../include/scene.h"
#include "../include/ecs.h"


static void scene_load_player() {
	// player
	const poke::entity_t playerEntity = poke::gEcs.entityCreate(POKE_PLAYER_ZINDEX, true);	
	poke::gEcs.addComponent<poke::player_t>(playerEntity, poke::player_t{});
	poke::gEcs.addComponent<poke::sprite_t>(
		playerEntity,
		poke::sprite_t{
			ASSETS_PATH "graphics/characters/player.png",
			{(float)POKE_PLAYER_WIDTH, (float)POKE_PLAYER_WIDTH}
		}
	);
	poke::gEcs.addComponent<poke::rigid_body_t>(playerEntity, poke::rigid_body_t{ .speed = POKE_PLAYER_MOVEMENT_SPEED });
	poke::gEcs.getTransform(playerEntity).size = { (float)POKE_PLAYER_WIDTH, (float)POKE_PLAYER_WIDTH };	

	// player shadow	
	const poke::entity_t playerShadowEntity = poke::gEcs.entityCreate(POKE_SHADOW_ZINDEX, true);
	poke::gEcs.getComponent<poke::player_t>(playerEntity).playerShadowEntity = playerShadowEntity;
	poke::gEcs.addComponent<poke::sprite_t>(playerShadowEntity, poke::sprite_t{ ASSETS_PATH "graphics/other/shadow.png" });
	poke::sprite_t& shadowSprite = poke::gEcs.getComponent<poke::sprite_t>(playerShadowEntity);
	poke::gEcs.getTransform(playerShadowEntity).size = { shadowSprite.rect.width, shadowSprite.rect.height };		
}


poke::LevelScreen::LevelScreen() {
	scene_load_player();	
}


void poke::LevelScreen::update() {
	const float dt = GetFrameTime();
	poke::gEcs.update(dt);
}


void poke::LevelScreen::draw() {	
	BeginDrawing();
	ClearBackground(LIGHTGRAY);
	poke::gEcs.draw();
	EndDrawing();
}
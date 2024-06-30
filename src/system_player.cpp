#include "../include/system.h"
#include "../include/ecs.h"
#include "../include/util.h"


void poke::PlayerSystem::update(const float dt) {
	for (const poke::entity_t playerEntity : this->entities) {
		// player components
		poke::player_t& player = poke::gEcs.getComponent<poke::player_t>(playerEntity);
		const poke::transform_t& playerTransform = poke::gEcs.getTransform(playerEntity);
		poke::rigid_body_t& playerRigidBody = poke::gEcs.getComponent<poke::rigid_body_t>(playerEntity);
		poke::sprite_t& playerSprite = poke::gEcs.getComponent<poke::sprite_t>(playerEntity);
		poke::transform_t& playerShadowTransform = poke::gEcs.getTransform(player.playerShadowEntity);

		// update shadow pos
		playerShadowTransform.pos.x = (playerTransform.pos.x + playerTransform.size.x / 2.0f) - playerShadowTransform.size.x / 2.0f;
		playerShadowTransform.pos.y = (playerTransform.pos.y + playerTransform.size.y / 2.0f) + 45.0f;

		// movement
		playerRigidBody.direction = { 0 };

		if (IsKeyDown(KEY_LEFT)) {
			playerRigidBody.direction.x = -1.0f;
		}
		else if (IsKeyDown(KEY_RIGHT)) {
			playerRigidBody.direction.x = 1.0f;
		}

		if (IsKeyDown(KEY_UP)) {
			playerRigidBody.direction.y = -1.0f;
		}
		else if (IsKeyDown(KEY_DOWN)) {
			playerRigidBody.direction.y = 1.0f;
		}

		// animation
		if (
			playerTransform.lastDirection[0] != playerTransform.direction[0] ||
			playerTransform.lastDirection[1] != playerTransform.direction[1]
			) {
			player.currentSprite = 0;
		}
		player.currentFrame++;
		if (player.currentFrame >= POKE_PLAYER_ANIMATION_SPEED) {
			player.currentFrame = 0;
			player.currentSprite++;
			if (player.currentSprite >= 4) {
				player.currentSprite = 0;
			}
			poke::applyCharacterSpriteRect(&playerSprite.rect, playerTransform.direction, player.currentSprite);
		}

	}
	
}


void poke::PlayerSystem::draw([[maybe_unused]] const poke::entity_t e) {

}
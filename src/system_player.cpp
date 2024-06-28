#include "../include/system.h"
#include "../include/ecs.h"


void poke::PlayerSystem::update(const float dt) {
	poke::player_t& player = poke::gPlayer;
	
	const poke::transform_t& playerTransform = poke::gEcs.getTransform(player.playerEntity);
	poke::rigid_body_t& playerRigidBody = poke::gEcs.getComponent<poke::rigid_body_t>(player.playerEntity);

	char lastState[3] = { player.direction[0], player.direction[1], player.action };
	
	playerRigidBody.direction = { 0 };

	if (IsKeyDown(KEY_LEFT)) {
		playerRigidBody.direction.x = -1.0f;
		player.direction[1] = 'l';
	}
	else if (IsKeyDown(KEY_RIGHT)) {
		playerRigidBody.direction.x = 1.0f;
		player.direction[1] = 'r';
	}

	if (IsKeyDown(KEY_UP)) {
		playerRigidBody.direction.y = -1.0f;
		player.direction[1] = 'u';
	}
	else if (IsKeyDown(KEY_DOWN)) {
		playerRigidBody.direction.y = 1.0f;
		player.direction[1] = 'd';
	}

	player.direction[0] = (playerRigidBody.direction.x == 0.0f && playerRigidBody.direction.y == 0.0f) ? 'i' : 'm';

	
}


void poke::PlayerSystem::draw([[maybe_unused]] const poke::entity_t e) {

}
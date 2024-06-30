#include "../include/system.h"
#include "../include/ecs.h"



void poke::RigidBodySystem::update(const float dt) {
	for (const poke::entity_t e : this->entities) {
		poke::rigid_body_t& r = poke::gEcs.getComponent<poke::rigid_body_t>(e);
		poke::transform_t& t = poke::gEcs.getTransform(e);
		r.direction = Vector2Normalize(r.direction);
		
		const float distance = dt * r.speed;
		r.lastMovement.x = distance * r.direction.x;
		r.lastMovement.y = distance * r.direction.y;
		t.pos.x += r.lastMovement.x;
		t.pos.y += r.lastMovement.y;
		
		t.lastDirection[0] = t.direction[0];
		t.lastDirection[1] = t.direction[1];

		t.direction[0] = r.direction.x == 0.0f && r.direction.y == 0.0f ? 'i' : 'm';
		if (r.direction.y < 0.0f) {
			t.direction[1] = 'u';
		}
		else if (r.direction.y > 0.0f) {
			t.direction[1] = 'd';
		}
		if (r.direction.x > 0.0f) {
			t.direction[1] = 'r';
		}
		else if (r.direction.x < 0.0f) {
			t.direction[1] = 'l';
		}
	}
}


void poke::RigidBodySystem::draw([[maybe_unused]] const poke::entity_t e) {

}
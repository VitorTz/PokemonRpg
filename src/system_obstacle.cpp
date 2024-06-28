#include "../include/system.h"
#include "../include/component.h"
#include "../include/ecs.h"



void poke::ObstacleSystem::update(const float dt) {
	for (const poke::entity_t e : this->entities) {
		poke::obstacle_t& o = poke::gEcs.getComponent<poke::obstacle_t>(e);
		const poke::transform_t& t = poke::gEcs.getComponent<poke::transform_t>(e);
		o.rect.width = t.size.x * o.hitbox.x;
		o.rect.height = t.size.y * o.hitbox.y;
		o.rect.x = (t.size.x - o.rect.width) / 2.0f;
		o.rect.y = (t.size.y - o.rect.height) / 2.0f;
	}
}


void poke::ObstacleSystem::draw([[maybe_unused]] const poke::entity_t e) {

}
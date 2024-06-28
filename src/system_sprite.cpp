#include "../include/system.h"
#include "../include/ecs.h"


void poke::SpriteSystem::update(const float dt) {

}


void poke::SpriteSystem::draw(const poke::entity_t e) {
	const poke::transform_t& t = poke::gEcs.getTransform(e);
	const poke::sprite_t& s = poke::gEcs.getComponent<poke::sprite_t>(e);
	DrawTextureRec(s.texture, s.rect, t.pos, WHITE);	
}
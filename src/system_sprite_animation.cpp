#include "../include/system.h"
#include "../include/ecs.h"


void poke::SpriteAnimationSystem::update([[maybe_unused]] const float dt) {
	for (const poke::entity_t e : this->entities) {
		poke::sprite_animation_t& s = poke::gEcs.getComponent<poke::sprite_animation_t>(e);
		s.currentFrame++;
		if (s.currentFrame >= s.speed) {
			s.currentFrame = 0;
			s.currentSprite++;
			if (s.currentSprite >= s.maxSprites) {
				s.currentSprite = 0;
			}
			s.sprite.rect.x = (s.currentSprite % s.cols) * s.sprite.rect.width;
			s.sprite.rect.y = s.currentSprite / s.cols * s.sprite.rect.height;			
		}
	}
}


void poke::SpriteAnimationSystem::draw(const poke::entity_t e) {
	const poke::transform_t& t = poke::gEcs.getTransform(e);
	const poke::sprite_animation_t& s = poke::gEcs.getComponent<poke::sprite_animation_t>(e);
	DrawTextureRec(s.sprite.texture, s.sprite.rect, t.pos, WHITE);
}
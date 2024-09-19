//
// Created by vitor on 9/19/24.
//
#include "System.h"
#include "ECS.h"


void pk::SpriteAnimationSystem::update(float dt) {
    for (const pk::entity_t e : this->entities) {
        pk::sprite_animation_t& animation = pk::gEcs.getComponent<pk::sprite_animation_t>(e);
        pk::sprite_t& sprite = pk::gEcs.getComponent<pk::sprite_t>(e);
        animation.counter.update();
        const std::uint32_t spriteIndex = animation.counter.getCounter();
        animation.rect.left = (spriteIndex % animation.cols) * animation.rect.width;
        animation.rect.top = (spriteIndex / animation.cols) * animation.rect.height;
        sprite.sfSprite.setTextureRect(animation.rect);
    }
}


void pk::SpriteAnimationSystem::draw([[maybe_unused]] sf::RenderWindow &window, [[maybe_unused]] const pk::entity_t e) {

}



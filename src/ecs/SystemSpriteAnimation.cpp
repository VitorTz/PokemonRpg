//
// Created by vitor on 9/19/24.
//
#include "System.h"
#include "ECS.h"


void pk::SpriteAnimationSystem::update([[maybe_unused]] const float dt) {
    for (const pk::entity_t e : this->entities) {
        pk::sprite_animation_t& animation = pk::gEcs.getComponent<pk::sprite_animation_t>(e);
        animation.counter.update();
        const std::uint32_t spriteIndex = animation.counter.getCounter();
        animation.rect.left = (spriteIndex % animation.cols) * animation.rect.width;
        animation.rect.top = (spriteIndex / animation.cols) * animation.rect.height;
    }
}


void pk::SpriteAnimationSystem::draw([[maybe_unused]] sf::RenderWindow &window, [[maybe_unused]] const pk::entity_t e) {
    const pk::transform_t& t = pk::gEcs.getTransform(e);
    pk::sprite_animation_t& s = pk::gEcs.getComponent<pk::sprite_animation_t>(e);
    s.sprite.setTextureRect(s.rect);
    s.sprite.setPosition(t.pos);
    s.sprite.setScale(t.scale);
    s.sprite.setRotation(t.rotation);
    window.draw(s.sprite);
}



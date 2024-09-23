//
// Created by vitor on 9/21/24.
//
#include "ECS.h"
#include "System.h"


void pk::SpriteAnimationSystem::update(const float dt) {
    for (const pk::entity_t e : this->entities) {
        pk::sprite_animation_t& sprite_animation = pk::gEcs.getComponent<pk::sprite_animation_t>(e);
        sprite_animation.counter.update();
        const int i = sprite_animation.counter.getCounter();
        sprite_animation.rect.left = (i % sprite_animation.cols) * sprite_animation.rect.width;
        sprite_animation.rect.top = (i / sprite_animation.cols) * sprite_animation.rect.height;
    }
}


void pk::SpriteAnimationSystem::render(sf::RenderWindow &window, const pk::entity_t e) {
    const pk::transform_t& transform = pk::gEcs.getTransform(e);
    pk::sprite_animation_t& sprite_animation = pk::gEcs.getComponent<pk::sprite_animation_t>(e);
    sprite_animation.sprite.setTextureRect(sprite_animation.rect);
    sprite_animation.sprite.setScale(transform.scale);
    sprite_animation.sprite.setPosition(transform.pos);
    sprite_animation.sprite.setRotation(transform.rotation);
    window.draw(sprite_animation.sprite);
}


//
// Created by vitor on 9/21/24.
//
#include "System.h"
#include "ECS.h"


void pk::SpriteSystem::update(const float dt) {

}


void pk::SpriteSystem::render(sf::RenderWindow &window, const pk::entity_t e) {
    const pk::transform_t& transform = pk::gEcs.getTransform(e);
    pk::sprite_t& sprite = pk::gEcs.getComponent<pk::sprite_t>(e);
    sprite.spr.setPosition(transform.pos);
    sprite.spr.setScale(transform.scale);
    sprite.spr.setRotation(transform.rotation);
    window.draw(sprite.spr);
}




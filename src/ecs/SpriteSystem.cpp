//
// Created by vitor on 9/28/24.
//
#include "System.h"
#include "ECS.h"


void pk::SpriteSystem::update(const float dt) {

}


void pk::SpriteSystem::draw(const pk::entity_t e) {
    const pk::transform_t& transform = pk::gEcs.getTransform(e);
    const pk::sprite_t& sprite = pk::gEcs.getComponent<pk::sprite_t>(e);
    DrawTextureV(sprite.texture, Vector2{transform.rect.x, transform.rect.y}, WHITE);
}



//
// Created by vitor on 10/1/24.
//
#include "ECS.h"
#include "System.h"


pk::SpriteSystem::SpriteSystem(const pk::TiledMapId mapId) : pk::System(mapId) {

}


void pk::SpriteSystem::update([[maybe_unused]] const float dt) {

}


void pk::SpriteSystem::draw(const pk::entity_t e) {
    pk::ECS* ecs = pk::ECS::getInstance(this->mapId);
    const pk::transform_t& transform = ecs->getTransform(e);
    const pk::sprite_t& sprite = ecs->getComponent<pk::sprite_t, id::sprite>(e);
    DrawTextureV(sprite.texture, transform.pos, WHITE);
}

//
// Created by vitor on 10/1/24.
//
#include "components.h"
#include "ECS.h"


pk::SpriteAnimationSystem::SpriteAnimationSystem(const pk::TiledMapId mapId) : pk::System(mapId) {

}


void pk::SpriteAnimationSystem::update([[maybe_unused]] const float dt) {
    pk::ECS* ecs = pk::ECS::getInstance(this->mapId);
    for (const pk::entity_t e : this->entities) {
        pk::sprite_animation_t& animation = ecs->getComponent<pk::sprite_animation_t, id::sprite_animation>(e);
        animation.counter++;
        if (animation.counter > animation.speed) {
            animation.counter = 0;
            animation.frame = (animation.frame + 1) % animation.maxFrame;
            animation.rect.x = static_cast<float>(animation.frame % animation.cols) * animation.rect.width;
            animation.rect.y = static_cast<float>(animation.frame / animation.cols) * animation.rect.height;
        }
    }
}


void pk::SpriteAnimationSystem::draw([[maybe_unused]] const pk::entity_t e) {
    pk::ECS* ecs = pk::ECS::getInstance(this->mapId);
    const pk::transform_t& transform = ecs->getTransform(e);
    const pk::sprite_animation_t& animation = ecs->getComponent<pk::sprite_animation_t, id::sprite_animation>(e);
    DrawTextureRec(animation.texture, animation.rect, transform.pos, WHITE);
}

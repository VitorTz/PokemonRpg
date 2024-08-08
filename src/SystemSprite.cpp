#include "../include/System.hpp"
#include "../include/Ecs.hpp"
#include <stdio.h>


void pk::SpriteSystem::update(const float dt) {

}


void pk::SpriteSystem::draw(const pk::entity_t e) {
    const pk::sprite_t& sprite = pk::gEcs.getComponent<pk::sprite_t>(e);
    const pk::transform_t& transform = pk::gEcs.getComponent<pk::transform_t>(e);    
    DrawTextureV(sprite.texture, transform.pos, WHITE);
}

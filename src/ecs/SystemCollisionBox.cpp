//
// Created by vitor on 9/14/24.
//
#include "System.h"
#include "ECS.h"


void pk::CollisionBoxSystem::update([[maybe_unused]] const float dt) {
    for (const pk::entity_t e : this->entities) {
        const pk::transform_t& t = pk::gEcs.getTransform(e);
        pk::collision_box_t& c = pk::gEcs.getComponent<pk::collision_box_t>(e);
        c.rect.left = (t.pos.x + t.size.x / 2.0f) - c.rect.width / 2.0f;
        c.rect.top = (t.pos.y + t.size.y / 2.0f) - c.rect.height / 2.0f;
    }
}


void pk::CollisionBoxSystem::draw(
    [[maybe_unused]] sf::RenderWindow &window, [[maybe_unused]] pk::entity_t e
) {

}



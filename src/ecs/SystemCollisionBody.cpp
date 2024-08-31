#include "../../include/ecs/System.hpp"
#include "../../include/ecs/ECS.hpp"


void pk::CollisionBodySystem::update(const float dt) {
    for (const pk::entity_t e : this->entities) {
        const pk::transform_t& t = pk::gEcs.getComponent<pk::transform_t>(e);
        pk::collision_body_t& c = pk::gEcs.getComponent<pk::collision_body_t>(e);
        c.rect.left = t.pos.x + c.offset.x;
        c.rect.top = t.pos.y + c.offset.y;
    }
}


void pk::CollisionBodySystem::draw(sf::RenderWindow& window, const pk::entity_t e) {
    
}
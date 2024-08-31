#include "../../include/ecs/System.hpp"
#include "../../include/ecs/ECS.hpp"


void pk::SpriteSystem::update(const float dt) {

}


void pk::SpriteSystem::draw(sf::RenderWindow& window, const pk::entity_t e) {
    pk::sprite_t& s = pk::gEcs.getComponent<pk::sprite_t>(e);
    const pk::transform_t& t = pk::gEcs.getComponent<pk::transform_t>(e);
    s.sfSprite.setPosition(t.pos);
    s.sfSprite.setScale(t.scale);
    s.sfSprite.setRotation(t.rotation);
    window.draw(s.sfSprite);    
}
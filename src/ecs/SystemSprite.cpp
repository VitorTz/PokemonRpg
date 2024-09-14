//
// Created by vitor on 9/14/24.
//
#include "System.h"
#include "ECS.h"


void pk::SpriteSystem::update([[maybe_unused]] const float dt) {

}


void pk::SpriteSystem::draw(sf::RenderWindow &window, const pk::entity_t e) {
    const pk::transform_t& t = pk::gEcs.getTransform(e);
    pk::sprite_t& s = pk::gEcs.getComponent<pk::sprite_t>(e);
    s.sfSprite.setPosition(t.pos);
    s.sfSprite.setScale(t.scale);
    s.sfSprite.setRotation(t.rotation);
    window.draw(s.sfSprite);
}



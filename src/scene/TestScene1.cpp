//
// Created by vitor on 9/14/24.
//
#include "Scene.h"


sf::Vector2f center{pk::SCREEN_CENTERX, pk::SCREEN_CENTERY};
const float speed = 1050.0f;

pk::TestScene1::TestScene1() {
    pk::entity_t e{};
    e = pk::gEcs.entityCreate(0, true);
    pk::addSpriteToEntity(e, ASSETS_PATH "data/maps/world.png");

    e = pk::gEcs.entityCreate(1, true);
    pk::gEcs.insertComponent<pk::water_t>(e, pk::water_t{});

    e = pk::gEcs.entityCreate(1, true);
    pk::gEcs.insertComponent<pk::water_t>(e, pk::water_t{true});
}


void pk::TestScene1::update(const float dt) {
    pk::gEcs.update(dt);
    sf::Vector2f d = pk::getMoveDirection();
    center.x += d.x * dt * speed;
    center.y += d.y * dt * speed;
    pk::gCamera.setCenter(center);
}


void pk::TestScene1::render(sf::RenderWindow &window) {
    pk::gEcs.draw(window);
}



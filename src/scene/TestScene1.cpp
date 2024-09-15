//
// Created by vitor on 9/14/24.
//
#include "Scene.h"


sf::Vector2f center{pk::WORLD_CENTERX, pk::WORLD_HEIGHT - pk::SCREEN_HF};
const float speed = 1050.0f;

pk::TestScene1::TestScene1() {
    pk::entity_t e{};
    // Map World
        e = pk::gEcs.entityCreate(0, true);
        pk::addSpriteToEntity(e, ASSETS_PATH "data/maps/world.png");

    // Water
        e = pk::gEcs.entityCreate(1, true);
        pk::gEcs.insertComponent<pk::water_t>(e, pk::water_t{});

        e = pk::gEcs.entityCreate(1, true);
        pk::gEcs.insertComponent<pk::water_t>(e, pk::water_t{true});

    // Boat System
        e = pk::gEcs.entityCreate(2, true);
        pk::gEcs.insertComponent<pk::boat_t>(e, pk::boat_t{});
        pk::gEcs.insertComponent<pk::sprite_t>(e, pk::sprite_t{});
        pk::gEcs.insertComponent<pk::bezier_curve_t>(e, pk::bezier_curve_t{});

        e = pk::gEcs.entityCreate(2, true);
        pk::gEcs.insertComponent<pk::boat_t>(e, pk::boat_t{});
        pk::gEcs.insertComponent<pk::sprite_t>(e, pk::sprite_t{});
        pk::gEcs.insertComponent<pk::bezier_curve_t>(e, pk::bezier_curve_t{});

        e = pk::gEcs.entityCreate(2, true);
        pk::gEcs.insertComponent<pk::boat_t>(e, pk::boat_t{});
        pk::gEcs.insertComponent<pk::sprite_t>(e, pk::sprite_t{});
        pk::gEcs.insertComponent<pk::bezier_curve_t>(e, pk::bezier_curve_t{});

}


void pk::TestScene1::update(const float dt) {
    pk::gEcs.update(dt);
    const sf::Vector2f d = pk::getMoveDirection();
    center.x += d.x * dt * speed;
    center.y += d.y * dt * speed;
    pk::gCamera.setCenter(center);
}


void pk::TestScene1::render(sf::RenderWindow &window) {
    pk::gEcs.draw(window);
}



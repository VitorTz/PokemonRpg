//
// Created by vitor on 9/21/24.
//
#include "Scene.h"
#include "../ecs/ECS.h"


pk::TestScene1::TestScene1() {
    pk::gEcs.createSpriteEntity(0, ASSETS_PATH "data/maps/player.png", sf::Vector2f(0.0f, 0.0f));
}


void pk::TestScene1::update(const float dt) {
    pk::gEcs.update(dt);
}


void pk::TestScene1::render(sf::RenderWindow &window) {
    pk::gEcs.draw(window);
}


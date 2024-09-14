//
// Created by vitor on 9/14/24.
//
#include "Scene.h"


pk::LevelScene::LevelScene() {
    pk::entity_t e{};

    // world map
    e = pk::gEcs.entityCreate(0, true);
    pk::addSpriteToEntity(e, ASSETS_PATH "data/maps/world.png");
}


void pk::LevelScene::update(const float dt) {
    pk::gEcs.update(dt);
}


void pk::LevelScene::render(sf::RenderWindow &window) {
    pk::gEcs.draw(window);
}



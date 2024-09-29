//
// Created by vitor on 9/28/24.
//
#include "Scene.h"
#include "../ecs/ECS.h"


pk::LevelScene::LevelScene() {
    pk::gCamera.reset();
    pk::entity_t e = pk::gEcs.createSprite(0, ASSETS_PATH "icons/Pokemon-Title.png");
}


void pk::LevelScene::update(const float dt) {
    pk::gEcs.update(dt);
}


void pk::LevelScene::draw() {
    pk::gEcs.draw();
}



//
// Created by vitor on 9/28/24.
//
#include "Scene.h"
#include "../ecs/ECS.h"


pk::LevelScene::LevelScene() {
    pk::gCamera.reset();
    pk::entity_t e = pk::gEcs.entityCreate(0, true);
    pk::gEcs.addComponent(e, pk::sprite_t{ASSETS_PATH "icons/Pokemon-Title.png"});
    pk::transform_t& t = pk::gEcs.getTransform(e);
    const auto& s = pk::gEcs.getComponent<pk::sprite_t>(e);
    t.size = Vector2{static_cast<float>(s.texture.width),  static_cast<float>(s.texture.height)};
}


void pk::LevelScene::update(const float dt) {
    pk::gEcs.update(dt);
}


void pk::LevelScene::draw() {
    pk::gEcs.draw();
}



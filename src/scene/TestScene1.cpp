//
// Created by vitor on 9/30/24.
//
#include "Scene.h"
#include "../ecs/ECS.h"
#include "../util/Camera.h"
#include "../util/TiledMap.h"


pk::TestScene1::TestScene1() {
    pk::gCamera.reset();
    pk::gEcs.unloadAllEntities();
    pk::gTiledMap.loadMap(pk::WorldMapId);
    pk::gEcs.createSprite(0, TILED_MAP_PATH "world/world.png");
    pk::gEcs.createPlayer();
}


void pk::TestScene1::update(const float dt) {
    pk::gEcs.update(dt);
    pk::gCamera.handleMouseWheelInput();
}


void pk::TestScene1::draw() {
    pk::gEcs.draw();
}


//
// Created by vitor on 9/30/24.
//
#include "Scene.h"
#include "../ecs/ECS.h"


pk::TestScene1::TestScene1() {
    pk::ECS::createInstance(pk::WorldMapId);
}


void pk::TestScene1::update(const float dt) {
    pk::ECS::updateInstance(pk::WorldMapId, dt);
}


void pk::TestScene1::draw() {
    pk::ECS::drawInstance(pk::WorldMapId);
}


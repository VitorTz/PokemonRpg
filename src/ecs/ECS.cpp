//
// Created by vitor on 10/1/24.
//
#include "ECS.h"


std::unordered_map<pk::TiledMapId, std::unique_ptr<pk::ECS>> pk::ECS::ecsInstanceMap{};


void pk::ECS::createInstance(const pk::TiledMapId mapId) {
    assert(pk::ECS::ecsInstanceMap.find(mapId) == pk::ECS::ecsInstanceMap.end());
    pk::ECS::ecsInstanceMap.emplace(mapId, std::unique_ptr<pk::ECS>(new pk::ECS(mapId)));
    pk::ECS::ecsInstanceMap[mapId]->init();
}


void pk::ECS::deleteInstance(const pk::TiledMapId mapId) {
    pk::ECS::ecsInstanceMap.erase(mapId);
}


pk::ECS *pk::ECS::getInstance(const pk::TiledMapId mapId) {
    assert(pk::ECS::ecsInstanceMap.find(mapId) != pk::ECS::ecsInstanceMap.end());
    return pk::ECS::ecsInstanceMap[mapId].get();
}


void pk::ECS::updateInstance(const pk::TiledMapId mapId, float dt) {
    assert(pk::ECS::ecsInstanceMap.find(mapId) != pk::ECS::ecsInstanceMap.end());
    pk::ECS::ecsInstanceMap[mapId]->update(dt);
}


void pk::ECS::drawInstance(const pk::TiledMapId mapId) {
    assert(pk::ECS::ecsInstanceMap.find(mapId) != pk::ECS::ecsInstanceMap.end());
    pk::ECS::ecsInstanceMap[mapId]->draw();
}


void pk::ECS::deleteAllInstances() {
    pk::ECS::ecsInstanceMap.clear();
}

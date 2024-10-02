//
// Created by vitor on 9/30/24.
//
#include "ECS.h"
#include "../util/Camera.h"


pk::SystemManager::SystemManager(const pk::TiledMapId mapId) : pk::EcsManager(mapId) {
    for (pk::entity_t e = 0; e < pk::MAX_ENTITIES; e++) {
        this->entityToComponents[e].reserve(pk::NUM_COMPONENTS);
    }
    this->systemMap.emplace(id::transform, std::make_unique<pk::TransformSystem>(mapId));
    this->systemMap.emplace(id::sprite, std::make_unique<pk::SpriteSystem>(mapId));
    this->systemMap.emplace(id::sprite_animation, std::make_unique<pk::SpriteAnimationSystem>(mapId));
    assert(this->systemMap.size() == pk::NUM_COMPONENTS);
    this->systemMap.emplace(id::player, std::make_unique<pk::PlayerSystem>(mapId));

    for (auto& pair : this->systemMap) {
        pair.second->entities.reserve(pk::MAX_ENTITIES);
    }
    this->systemOrder.push_back(id::sprite_animation);
    this->systemOrder.push_back(id::player);
}


void pk::SystemManager::insert(const pk::entity_t e, const pk::component_t componentId) {
    this->systemMap[componentId]->entities.insert(e);
    this->entityToComponents[e].insert(componentId);
}


void pk::SystemManager::erase(const pk::entity_t e, const pk::component_t componentId) {
    this->systemMap[componentId]->entities.erase(e);
    this->entityToComponents[e].erase(componentId);
}


void pk::SystemManager::entityDestroy(const pk::entity_t e) {
    for (const pk::component_t id : this->entityToComponents[e]) {
        this->systemMap[id]->entities.erase(e);
    }
    this->entityToComponents[e].clear();
}


void pk::SystemManager::update(const float dt) {
    for (const pk::component_t id : this->systemOrder) {
        this->systemMap[id]->update(dt);
    }
}


void pk::SystemManager::draw(const std::vector<std::pair<float, pk::entity_t>>& entities) {
    for (const std::pair<float, pk::entity_t>& pair : entities) {
        for (const pk::component_t id : this->entityToComponents[pair.second]) {
            this->systemMap[id]->draw(pair.second);
        }
    }
}


void pk::SystemManager::clear() {
    for (auto& pair : this->entityToComponents) {
        pair.second.clear();
    }
    for (auto& pair : this->systemMap) {
        pair.second->entities.clear();
    }
}




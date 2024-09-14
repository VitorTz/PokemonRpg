//
// Created by vitor on 9/14/24.
//
#include "EntityManager.h"


pk::EntityManager::EntityManager() {
    for (pk::entity_t e = 0; e < pk::MAX_ENTITIES; e++) {
        this->entities.push(e);
    }
}


pk::entity_t pk::EntityManager::entityCreate() {
    assert(this->mSize < pk::MAX_ENTITIES);
    const pk::entity_t e = this->entities.front();
    this->entities.pop();
    this->mSize++;
    return e;
}


void pk::EntityManager::entityDestroy(pk::entity_t e) {
    this->entities.push(e);
    this->mSize--;
}


void pk::EntityManager::clear() {
    this->entities = std::queue<pk::entity_t>();
    for (pk::entity_t e = 0; e < pk::MAX_ENTITIES; e++) {
        this->entities.push(e);
    }
    this->mSize = 0;
}


std::size_t pk::EntityManager::size() const {
    return this->mSize;
}






//
// Created by vitor on 9/30/24.
//
#include "Entity.h"


pk::EntityManager::EntityManager() {
    for (pk::entity_t e = 0; e < pk::MAX_ENTITIES; e++) {
        this->q.push(e);
    }
}


pk::entity_t pk::EntityManager::entityCreate() {
    assert(this->mSize < pk::MAX_ENTITIES);
    const pk::entity_t e = this->q.front();
    this->q.pop();
    this->mSize++;
    return e;
}


void pk::EntityManager::entityDestroy(const pk::entity_t e) {
    this->q.push(e);
    this->mSize--;
}


void pk::EntityManager::clear() {
    this->q = std::queue<pk::entity_t>();
    for (pk::entity_t e = 0; e < pk::MAX_ENTITIES; e++) {
        this->q.push(e);
    }
    this->mSize = 0;
}


std::size_t pk::EntityManager::size() const {
    return this->mSize;
}






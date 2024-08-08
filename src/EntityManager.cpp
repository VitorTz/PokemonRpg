#include "../include/EntityManager.hpp"
#include <cassert>


pk::EntityManager::EntityManager() {
    for (pk::entity_t e = 0; e < pk::MAX_ENTITIES; e++) {
        this->queue.push(e);
    }
}


pk::entity_t pk::EntityManager::entityCreate() {
    assert(this->mSize < pk::MAX_ENTITIES);
    const pk::entity_t e = this->queue.front();
    this->queue.pop();
    this->mSize++;
    return e;
}


void pk::EntityManager::entityDestroy(const pk::entity_t e) {
    this->queue.push(e);
    this->mSize--;
}


void pk::EntityManager::clear() {
    this->queue = std::queue<pk::entity_t>();
    this->mSize = 0;
    for (pk::entity_t e = 0; e < pk::MAX_ENTITIES; e++) {
        this->queue.push(e);
    }
}


std::size_t pk::EntityManager::size() const {
    return this->mSize;
}
#include "../../include/ecs/EntityManager.hpp"
#include "../../include/util.hpp"


pk::EntityManager::EntityManager() {
    for (pk::entity_t e = 0; e < pk::MAX_ENTITIES; e++) {
        this->queue.push(e);
    }
}


pk::entity_t pk::EntityManager::entityCreate() {
    pk::mAssert(this->mSize < pk::MAX_ENTITIES, "[MAX NUM ENTITIES EXCEDDED]");
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
    for (pk::entity_t e = 0; e < pk::MAX_ENTITIES; e++) {
        this->queue.push(e);
    }
    this->mSize = 0;
}


std::size_t pk::EntityManager::size() const {
    return this->mSize;
}
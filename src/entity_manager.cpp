#include "../include/entity_manager.h"


poke::EntityManager::EntityManager() {
	for (poke::entity_t e = 0; e < POKE_MAX_ENTITIES; e++) {
		this->queue.push(e);
	}	
}


poke::entity_t poke::EntityManager::entityCreate() {
	assert(this->mSize < POKE_MAX_ENTITIES);
	const poke::entity_t e = this->queue.front();
	this->queue.pop();
	this->mSize++;
	return e;
}


void poke::EntityManager::entityDestroy(const poke::entity_t e) {
	this->queue.push(e);
	this->mSize--;
}

void poke::EntityManager::clear() {
	this->queue = std::queue<poke::entity_t>();
	for (poke::entity_t e = 0; e < POKE_MAX_ENTITIES; e++) {
		this->queue.push(e);
	}
	this->mSize = 0;
}


std::size_t poke::EntityManager::size() const {
	return this->mSize;
}
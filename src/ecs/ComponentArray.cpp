//
// Created by vitor on 9/14/24.
//
#include "ComponentArray.h"


template<typename T>
pk::ComponentArray<T>::ComponentArray() {
    this->entityToIndex.reserve(pk::MAX_ENTITIES);
    this->indexToEntity.reserve(pk::MAX_ENTITIES);
}


template<typename T>
void pk::ComponentArray<T>::insert(pk::entity_t e, T c) {
    this->entityToIndex[e] = this->mSize;
    this->indexToEntity[this->mSize] = e;
    this->arr[this->mSize++] = c;
}


template<typename T>
void pk::ComponentArray<T>::erase(pk::entity_t e) {
    if (this->entityToIndex.find(e) == this->entityToIndex.end()) {
        return;
    }
    const std::size_t indexOfLastComponent = this->mSize--;
    const pk::entity_t lastEntity = this->indexToEntity[indexOfLastComponent];
    const std::size_t indexOfRemovedComponent = this->entityToIndex[e];

    this->arr[indexOfRemovedComponent] = this->arr[indexOfLastComponent];

    this->entityToIndex[lastEntity] = indexOfRemovedComponent;
    this->indexToEntity[indexOfRemovedComponent] = lastEntity;

    this->entityToIndex.erase(e);
    this->indexToEntity.erase(indexOfLastComponent);
}

template<typename T>
T &pk::ComponentArray<T>::at(pk::entity_t e) {
    assert(this->entityToIndex.find(e) != this->entityToIndex.end());
    return this->arr[this->entityToIndex[e]];
}


template<typename T>
void pk::ComponentArray<T>::clear() {
    this->entityToIndex.clear();
    this->indexToEntity.clear();
    this->mSize = 0;
}


template<typename T>
std::size_t pk::ComponentArray<T>::size() const {
    return this->mSize;
}





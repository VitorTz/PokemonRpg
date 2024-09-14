//
// Created by vitor on 9/14/24.
//

#ifndef COMPONENTARRAY_H
#define COMPONENTARRAY_H
#include "../pokemon.h"

namespace pk {

    class IComponentArray {

    public:
        virtual ~IComponentArray() = default;
        virtual void erase(pk::entity_t e) = 0;
        virtual void clear() = 0;
        virtual std::size_t size() const = 0;
    };


    template<typename T>
    class ComponentArray : public pk::IComponentArray {

    private:
        std::array<T, pk::MAX_ENTITIES> arr{};
        std::unordered_map<pk::entity_t, std::size_t> entityToIndex{};
        std::unordered_map<std::size_t, pk::entity_t> indexToEntity{};
        std::size_t mSize{};

    public:
        ComponentArray() {
            this->entityToIndex.reserve(pk::MAX_ENTITIES);
            this->indexToEntity.reserve(pk::MAX_ENTITIES);
        }

        void insert(pk::entity_t e, T c) {
            this->entityToIndex[e] = this->mSize;
            this->indexToEntity[this->mSize] = e;
            this->arr[this->mSize++] = c;
        }

        void erase(pk::entity_t e) override {
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

        T& at(pk::entity_t e) {
            assert(this->entityToIndex.find(e) != this->entityToIndex.end());
            return this->arr[this->entityToIndex[e]];
        }

        void clear() override {
            this->entityToIndex.clear();
            this->indexToEntity.clear();
            this->mSize = 0;
        }

        std::size_t size() const override {
            return this->mSize;
        }

    };

}



#endif //COMPONENTARRAY_H

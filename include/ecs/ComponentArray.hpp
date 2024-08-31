#pragma once
#include <unordered_map>
#include <array>
#include "../constants.hpp"
#include "../types.hpp"


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

            T& at(const pk::entity_t e) {
                return this->arr[this->entityToIndex[e]];
            }

            void insert(const pk::entity_t e, T c) {
                this->entityToIndex[e] = this->mSize;
                this->indexToEntity[this->mSize] = e;
                this->arr[this->mSize++] = c;
            }

            void erase(const pk::entity_t e) {
                if (this->entityToIndex.find(e) == this->entityToIndex.end()) {
                    return;
                }
                const std::size_t lastComponentIndex = this->mSize--;
                const std::size_t removedComponentIndex = this->entityToIndex[e];
                const pk::entity_t lastEntity = this->indexToEntity[lastComponentIndex];

                this->entityToIndex[lastEntity] = removedComponentIndex;
                this->indexToEntity[removedComponentIndex] = lastEntity;

                this->entityToIndex.erase(e);
                this->indexToEntity.erase(lastComponentIndex);                
            }

            void clear() {
                this->entityToIndex.clear();
                this->indexToEntity.clear();
                this->mSize = 0;
            }

            std::size_t size() const override {
                return this->mSize;
            }

    };
    
} // namespace pk

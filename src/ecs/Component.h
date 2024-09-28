//
// Created by vitor on 9/28/24.
//

#ifndef COMPONENT_H
#define COMPONENT_H
#include <array>
#include <cassert>
#include <unordered_map>
#include <memory>
#include "../util/constants.h"
#include "../util/TypeID.h"


namespace pk {

    class IComponentArray {

    public:
        virtual ~IComponentArray() = default;
        virtual void erase(pk::entity_t e) = 0;
        virtual void clear() = 0;
        virtual std::size_t size() const = 0;

    };

    template<typename T>
    class ComponentArray final : public pk::IComponentArray {

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

        void insert(const pk::entity_t e, T c) {
            assert(this->entityToIndex.find(e) == this->entityToIndex.end());
            this->entityToIndex[e] = this->mSize;
            this->indexToEntity[this->mSize] = e;
            this->arr[this->mSize++] = c;
        }

        void erase(const pk::entity_t e) override {
            if (this->entityToIndex.find(e) == this->entityToIndex.end()) {
                return;
            }

            const std::size_t lastIndex = --this->mSize;
            const std::size_t removedComponentIndex = this->entityToIndex[e];
            const pk::entity_t lastEntity = this->indexToEntity[lastIndex];

            this->arr[removedComponentIndex] = this->arr[lastIndex];

            this->entityToIndex[lastEntity] = removedComponentIndex;
            this->indexToEntity[removedComponentIndex] = lastEntity;

            this->entityToIndex.erase(e);
            this->indexToEntity.erase(lastIndex);
        }

        const std::array<T, pk::MAX_ENTITIES>& getArray() const {
            return this->arr;
        }

        T& at(const pk::entity_t e) {
            assert(this->entityToIndex.find(e) != this->entityToIndex.end());
            return this->arr[this->entityToIndex[e]];
        }

        typename std::array<T, pk::MAX_ENTITIES>::iterator begin() {
            return this->arr.begin();
        }

        typename std::array<T, pk::MAX_ENTITIES>::iterator end() {
            return this->arr.begin() + this->mSize;
        }

        T& atIndex(const std::size_t index) {
            assert(this->indexToEntity.find(index) != this->indexToEntity.end());
            return this->arr[index];
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


    class ComponentManager {


    private:
        std::unordered_map<pk::component_t, std::unique_ptr<pk::IComponentArray>> componentMap{};

    public:

        template<typename T>
        void registerComponent() {
            const pk::component_t id = pk::gTypeId.get<T>();
            assert(this->componentMap.find(id) == this->componentMap.end());
            this->componentMap.emplace(id, std::make_unique<pk::ComponentArray<T>>());
        }

        template<typename T>
        void insert(const pk::entity_t e, T c) {
            const pk::component_t id = pk::gTypeId.get<T>();
            dynamic_cast<pk::ComponentArray<T>*>(this->componentMap[id].get())->insert(e, std::move(c));
        }

        template<typename T>
        void erase(const pk::entity_t e) {
            const pk::component_t id = pk::gTypeId.get<T>();
            dynamic_cast<pk::ComponentArray<T>*>(this->componentMap[id].get())->erase(e);
        }

        template<typename T>
        T& at(const pk::entity_t e) {
            const pk::component_t id = pk::gTypeId.get<T>();
            return dynamic_cast<pk::ComponentArray<T>*>(this->componentMap[id].get())->at(e);
        }

        template<typename T>
        pk::ComponentArray<T>* getComponentArray() const {
            const pk::component_t id = pk::gTypeId.get<T>();
            return dynamic_cast<pk::ComponentArray<T>*>(this->componentMap.at(id).get());
        }

        void entityDestroy(const pk::entity_t e) {
            for (auto& pair : this->componentMap) {
                pair.second->erase(e);
            }
        }

        void clear() {
            for (auto& pair : this->componentMap) {
                pair.second->clear();
            }
        }

        std::size_t size() const {
            return this->componentMap.size();
        }

    };

}

#endif //COMPONENT_H

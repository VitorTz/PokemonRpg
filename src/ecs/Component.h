//
// Created by vitor on 9/30/24.
//

#ifndef COMPONENT_H
#define COMPONENT_H
#include "components.h"
#include "../pokemon.h"
#include "EcsManager.h"


namespace pk {

    class AbstractComponentArray {

    public:
        virtual ~AbstractComponentArray() = default;
        virtual void erase(pk::entity_t e) = 0;
        virtual void clear() = 0;
        virtual std::size_t size() const = 0;

    };


    template<typename T>
    class ComponentArray final : public pk::AbstractComponentArray {

    private:
        std::array<T, pk::MAX_ENTITIES> arr{};
        std::unordered_map<pk::entity_t, std::uint32_t> entityToIndex{};
        std::unordered_map<std::uint32_t, pk::entity_t> indexToEntity{};
        std::size_t mSize{};

    public:
        ComponentArray() {
            this->entityToIndex.reserve(pk::MAX_ENTITIES);
            this->indexToEntity.reserve(pk::MAX_ENTITIES);
        }

        void insert(const pk::entity_t e, T c) {
            this->entityToIndex[e] = this->mSize;
            this->indexToEntity[this->mSize] = e;
            this->arr[this->mSize++] = c;
        }

        void erase(const pk::entity_t e) override {
            if (this->entityToIndex.find(e) == this->entityToIndex.end()) {
                return;
            }
            const std::size_t lastEntityIndex = --this->mSize;
            const std::size_t removedComponentIndex = this->entityToIndex[e];
            const pk::entity_t lastEntity = this->indexToEntity[lastEntityIndex];

            this->arr[removedComponentIndex] = this->arr[lastEntityIndex];

            this->entityToIndex[lastEntity] = removedComponentIndex;
            this->indexToEntity[removedComponentIndex] = lastEntity;

            this->entityToIndex.erase(e);
            this->indexToEntity.erase(lastEntityIndex);
        }

        T& at(const pk::entity_t e) {
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

    class ComponentManager final : public pk::EcsManager {

    private:
        std::unordered_map<pk::component_t, std::unique_ptr<pk::AbstractComponentArray>> componentMap{};

    public:
        explicit ComponentManager(const pk::TiledMapId mapId) : pk::EcsManager(mapId) {
            this->componentMap.emplace(pk::id::transform, std::make_unique<pk::ComponentArray<pk::transform_t>>());
            this->componentMap.emplace(pk::id::sprite, std::make_unique<pk::ComponentArray<pk::sprite_t>>());
            this->componentMap.emplace(pk::id::sprite_animation, std::make_unique<pk::ComponentArray<pk::sprite_animation_t>>());
            assert(this->componentMap.size() == pk::NUM_COMPONENTS);
        }

        template<typename T, pk::component_t id>
        void insert(const pk::entity_t e, T c) {
            dynamic_cast<pk::ComponentArray<T>*>(this->componentMap[id].get())->insert(e, std::move(c));
        }

        template<typename T, pk::component_t id>
        void erase(const pk::entity_t e) {
            this->componentMap[id]->erase(e);
        }

        template<typename T, pk::component_t id>
        T& at(const pk::entity_t e) {
            return dynamic_cast<pk::ComponentArray<T>*>(this->componentMap[id].get())->at(e);
        }

        void entityDestroy(const pk::entity_t e) override {
            for (auto& pair : this->componentMap) {
                pair.second->erase(e);
            }
        }

        void clear() override {
            for (auto& pair : this->componentMap) {
                pair.second->clear();
            }
        }

    };

}


#endif //COMPONENT_H

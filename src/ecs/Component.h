//
// Created by vitor on 9/21/24.
//

#ifndef COMPONENT_H
#define COMPONENT_H
#include "components.h"
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
            this->entityToIndex[e] = this->mSize;
            this->indexToEntity[this->mSize] = e;
            this->arr[this->mSize++] = c;
        }

        void erase(const pk::entity_t e) override {
            if (this->entityToIndex.find(e) == this->entityToIndex.end()) {
                return;
            }
            const std::size_t lastComponentIndex = this->mSize--;
            const std::size_t removedComponentIndex = this->entityToIndex[e];
            const pk::entity_t lastEntity = this->indexToEntity[lastComponentIndex];
            this->entityToIndex[lastEntity] = removedComponentIndex;
            this->indexToEntity[removedComponentIndex] = lastEntity;

            this->arr[removedComponentIndex] = this->arr[lastComponentIndex];
            this->entityToIndex[lastEntity] = removedComponentIndex;
            this->indexToEntity[removedComponentIndex] = lastEntity;

            this->entityToIndex.erase(e);
            this->indexToEntity.erase(lastComponentIndex);
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

    class ComponentManager {

    private:
        std::unordered_map<pk::component_t, std::unique_ptr<pk::IComponentArray>> componentMap{};
        pk::ComponentArray<pk::transform_t>* transform{};

    public:
        ComponentManager() {
            this->componentMap.emplace(pk::gTypeId.get<pk::transform_t>(), std::make_unique<pk::ComponentArray<pk::transform_t>>());
            this->componentMap.emplace(pk::gTypeId.get<pk::sprite_t>(), std::make_unique<pk::ComponentArray<pk::sprite_t>>());
            this->componentMap.emplace(pk::gTypeId.get<pk::sprite_animation_t>(), std::make_unique<pk::ComponentArray<pk::sprite_animation_t>>());
            this->componentMap.emplace(pk::gTypeId.get<pk::collision_t>(), std::make_unique<pk::ComponentArray<pk::collision_t>>());
            this->componentMap.emplace(pk::gTypeId.get<pk::movement_t>(), std::make_unique<pk::ComponentArray<pk::movement_t>>());
            assert(this->componentMap.size() == pk::NUM_COMPONENTS - 1);
            this->transform = dynamic_cast<pk::ComponentArray<pk::transform_t>*>(this->componentMap.at(pk::gTypeId.get<pk::transform_t>()).get());
        }

        template<typename T>
        void insert(const pk::entity_t e, T c) {
            const pk::entity_t id = pk::gTypeId.get<T>();
            dynamic_cast<pk::ComponentArray<T>*>(this->componentMap[id].get())->insert(e, std::move(c));
        }

        template<typename T>
        void erase(const pk::entity_t e) {
            const pk::entity_t id = pk::gTypeId.get<T>();
            this->componentMap[id]->erase(e);
        }

        template<typename  T>
        T& at(const pk::entity_t e) {
            const pk::entity_t id = pk::gTypeId.get<T>();
            return dynamic_cast<pk::ComponentArray<T>*>(this->componentMap[id].get())->at(e);
        }

        pk::transform_t& getTransform(const pk::entity_t e) {
            return this->transform->at(e);
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
                std::size_t s{};
            for (auto& pair : this->componentMap) {
                s += pair.second->size();
            }
            return s;
        }

    };

}

#endif //COMPONENT_H

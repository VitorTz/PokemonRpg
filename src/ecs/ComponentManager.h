//
// Created by vitor on 9/14/24.
//

#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H
#include "../pokemon.h"
#include "../TypeId.h"
#include "components.h"
#include "ComponentArray.h"


namespace pk {

    class ComponentManager {

    private:
        std::unordered_map<pk::component_t, std::unique_ptr<pk::IComponentArray>> componentMap{};
        pk::ComponentArray<pk::transform_t>* transformArray{nullptr};

    public:
        ComponentManager() {
            this->componentMap.emplace(pk::gTypeId.get<pk::transform_t>(), std::make_unique<pk::ComponentArray<pk::transform_t>>());
            this->componentMap.emplace(pk::gTypeId.get<pk::sprite_t>(), std::make_unique<pk::ComponentArray<pk::sprite_t>>());
            this->componentMap.emplace(pk::gTypeId.get<pk::collision_box_t>(), std::make_unique<pk::ComponentArray<pk::collision_box_t>>());
            this->componentMap.emplace(pk::gTypeId.get<pk::collision_box_static_t>(), std::make_unique<pk::ComponentArray<pk::collision_box_static_t>>());
            this->componentMap.emplace(pk::gTypeId.get<pk::water_t>(), std::make_unique<pk::ComponentArray<pk::water_t>>());
            this->componentMap.emplace(pk::gTypeId.get<pk::bezier_curve_t>(), std::make_unique<pk::ComponentArray<pk::bezier_curve_t>>());
            this->componentMap.emplace(pk::gTypeId.get<pk::boat_t>(), std::make_unique<pk::ComponentArray<pk::boat_t>>());
            this->componentMap.emplace(pk::gTypeId.get<pk::sprite_animation_t>(), std::make_unique<pk::ComponentArray<pk::sprite_animation_t>>());
            assert(this->componentMap.size() == pk::NUM_VALID_COMPONENTS);
            this->transformArray = dynamic_cast<pk::ComponentArray<pk::transform_t>*>(this->componentMap[pk::gTypeId.get<pk::transform_t>()].get());
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

        pk::transform_t& getTransform(const pk::entity_t e) {
            return this->transformArray->at(e);
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


#endif //COMPONENTMANAGER_H

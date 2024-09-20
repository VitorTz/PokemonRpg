//
// Created by vitor on 9/14/24.
//

#ifndef SYSTEMANAGER_H
#define SYSTEMANAGER_H
#include "components.h"
#include "System.h"
#include "../pokemon.h"
#include "../util/TypeId.h"


namespace pk {

    class SystemManager {

    private:
        std::unordered_map<pk::component_t, std::unique_ptr<pk::System>> systemMap{};
        std::unordered_map<pk::entity_t, std::unordered_set<pk::entity_t>> entityToSystem{};  // Keeps track of systems for each entity
        std::vector<pk::component_t> systemOrder{};  // Order in which each System will be updated

    public:
        SystemManager() {
            this->systemMap.reserve(pk::NUM_COMPONENTS);
            // Create System for each Component
            this->systemMap.emplace(pk::gTypeId.get<pk::transform_t>(), std::make_unique<pk::TransformSystem>());
            this->systemMap.emplace(pk::gTypeId.get<pk::sprite_t>(), std::make_unique<pk::SpriteSystem>());
            this->systemMap.emplace(pk::gTypeId.get<pk::collision_box_t>(), std::make_unique<pk::CollisionBoxSystem>());
            this->systemMap.emplace(pk::gTypeId.get<pk::collision_box_static_t>(), std::make_unique<pk::CollisionBoxStaticSystem>());
            this->systemMap.emplace(pk::gTypeId.get<pk::water_t>(), std::make_unique<pk::WaterSystem>());
            this->systemMap.emplace(pk::gTypeId.get<pk::boat_t>(), std::make_unique<pk::BoatSystem>());
            this->systemMap.emplace(pk::gTypeId.get<pk::bezier_curve_t>(), std::make_unique<pk::BezierCurveSystem>());
            this->systemMap.emplace(pk::gTypeId.get<pk::sprite_animation_t>(), std::make_unique<pk::SpriteAnimationSystem>());
            this->systemMap.emplace(pk::gTypeId.get<pk::player_t>(), std::make_unique<pk::PlayerSystem>());
            assert(this->systemMap.size() == pk::NUM_COMPONENTS);

            // this->entityToSystem Keeps track of systems for each entity
            this->entityToSystem.reserve(pk::MAX_ENTITIES);
            for (pk::entity_t e = 0; e < pk::MAX_ENTITIES; e++) {
                this->entityToSystem[e].reserve(pk::NUM_COMPONENTS);
            }

            // Defines the order in which each System will be updated. Not all Systems need to be updated.
            this->systemOrder.reserve(pk::NUM_COMPONENTS);
            this->systemOrder.push_back(pk::gTypeId.get<pk::collision_box_t>());
            this->systemOrder.push_back(pk::gTypeId.get<pk::water_t>());
            this->systemOrder.push_back(pk::gTypeId.get<pk::boat_t>());
            this->systemOrder.push_back(pk::gTypeId.get<pk::bezier_curve_t>());
            this->systemOrder.push_back(pk::gTypeId.get<pk::sprite_animation_t>());
            this->systemOrder.push_back(pk::gTypeId.get<pk::player_t>());
        }

        /**
         * Insert the component T System on the entity e
         * @tparam T
         * @param e
         */
        template<typename T>
        void insert(const pk::entity_t e) {
            const pk::component_t id = pk::gTypeId.get<T>();
            this->systemMap[id]->entities.insert(e);
            this->entityToSystem[e].insert(id);
        }

        /**
         * Removes the component T System from the entity e
         * @tparam T component
         * @param e entity
         */
        template<typename T>
        void erase(const pk::entity_t e) {
            const pk::component_t id = pk::gTypeId.get<T>();
            this->systemMap[id]->entities.erase(e);
            this->entityToSystem[e].erase(id);
        }

        /**
         * Removes all Systems related to the entity
         */
        void entityDestroy(const pk::entity_t e) {
            for (auto& pair : this->systemMap) {
                pair.second->entities.erase(e);
            }
            this->entityToSystem[e].clear();
        }

        void update(const float dt) {
            for (const pk::component_t id : this->systemOrder) {
                this->systemMap[id]->update(dt);
            }
        }

        template<typename T>
        const std::unordered_set<pk::entity_t>& getEntitiesFromSystem() {
            const pk::component_t id = pk::gTypeId.get<T>();
            return this->systemMap[id]->entities;
        }

        void draw(sf::RenderWindow& window, const pk::OrderedEntityVector& v) {
            for (const std::pair<float, pk::entity_t>& pair : v) {
                for (const pk::component_t id : this->entityToSystem[pair.second]) {
                    this->systemMap[id]->draw(window, pair.second);
                }
            }
        }

        void clear() {
            for (auto& pair : this->systemMap) {
                pair.second->entities.clear();
            }
            for (auto& pair : this->entityToSystem) {
                pair.second.clear();
            }
        }

        std::size_t size() const {
            std::size_t s{};
            for (auto& pair : this->systemMap) {
                s += pair.second->entities.size();
            }
            return s;
        }

    };

}

#endif //SYSTEMANAGER_H

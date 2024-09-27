#pragma once
#include "../util/types.hpp"
#include <cstddef>
#include <memory>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "../util/globals.hpp"
#include "Component.hpp"


namespace pk {


    class System {

        public:
            std::unordered_set<pk::entity_t> entities{};

        public:
            virtual ~System() = default;
            virtual void update(float dt) = 0;
            virtual void draw(pk::entity_t e) = 0;

    };

    class TransformSystem : public pk::System {

        public:
            void update(float dt) override;
            void draw(pk::entity_t e) override;

    };

    class CollisionSystem : public pk::System {

        public:
            void update(float dt) override;
            void draw(pk::entity_t e) override;

    };

    class SpriteSystem : public pk::System {

        public:
            void update(float dt) override;
            void draw(pk::entity_t e) override;

    };


    class SpriteAnimationSystem : public pk::System {

        public:
            void update(float dt) override;
            void draw(pk::entity_t e) override;

    };


    class PlayerSystem : public pk::System {

        public:
            void update(float dt) override;
            void draw(pk::entity_t e) override;

    };


    class SystemManager {


        private:
            std::unordered_map<pk::component_t, std::unique_ptr<pk::System>> systemMap{};
            std::unordered_map<pk::entity_t, std::unordered_set<pk::component_t>> entityToSystem{};            
            std::vector<pk::component_t> systemOrder{};
 
        public:
            SystemManager() {
                for (pk::entity_t e = 0; e < pk::MAX_ENTITIES; e++) {
                    this->entityToSystem[e].reserve(32);
                }                
                this->systemOrder.push_back(pk::gTypeId.get<pk::sprite_t>());
                this->systemOrder.push_back(pk::gTypeId.get<pk::sprite_animation_t>());
                this->systemOrder.push_back(pk::gTypeId.get<pk::player_t>());                
            }
            
            template<typename T, typename S>
            void registerSystem() {
                this->systemMap.emplace(pk::gTypeId.get<T>(), std::make_unique<S>());
            }

            template<typename T>
            void insert(const pk::entity_t e) {
                const pk::component_t id = pk::gTypeId.get<T>();
                this->systemMap[id]->entities.insert(e);
                this->entityToSystem[e].insert(id);
            }

            template<typename T>
            void erase(const pk::entity_t e) {
                const pk::component_t id = pk::gTypeId.get<T>();
                this->systemMap[id]->entities.erase(e);
                this->entityToSystem[e].erase(id);
            }

            void entityDestroy(const pk::entity_t e) {
                for (auto& pair : this->systemMap) {
                    pair.second->entities.erase(e);
                }
            }

            void update(float dt) {
                for (const pk::component_t id : this->systemOrder) {
                    this->systemMap[id]->update(dt);
                }
            }

            void draw(const std::vector<std::pair<float, pk::entity_t>>& entities) {
                for (const std::pair<float, pk::entity_t>& pair : entities) {
                    for (const pk::component_t id : this->entityToSystem[pair.second]) {
                        this->systemMap[id]->draw(pair.second);
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

            std::size_t numSystem() const {
                return this->systemMap.size();
            }

    };

}
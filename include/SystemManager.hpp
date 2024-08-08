#pragma once
#include "System.hpp"
#include "constants.hpp"
#include "components.hpp"
#include "EcsManager.hpp"
#include "ComponentId.hpp"
#include <vector>
#include <unordered_map>
#include <memory>


namespace pk {


    class SystemManager : public pk::EcsManager {

        private:
            std::unordered_map<pk::component_t, std::unique_ptr<pk::System>> systemMap{};
            std::unordered_map<pk::entity_t, std::unordered_set<pk::component_t>> systemByEntity{};
            std::vector<pk::component_t> systemOrder{};
        
        private:
            template<typename T, typename S>
            void registerSystem() {
                const pk::component_t id = pk::getId<T>();
                assert(
                    this->systemMap.find(id) == this->systemMap.end() &&
                    "System already registered"
                );
                this->systemOrder.push_back(id);
                this->systemMap.emplace(id, std::make_unique<S>());
            }

        public:
            SystemManager() {
                this->systemMap.reserve(pk::NUM_COMPONENTS);
                this->systemOrder.reserve(pk::NUM_COMPONENTS);
                this->systemByEntity.reserve(pk::MAX_ENTITIES);
                for (pk::entity_t e = 0; e < pk::MAX_ENTITIES; e++) {
                    this->systemByEntity.insert({e, { }});
                }
                for (auto& pair : this->systemByEntity) {
                    pair.second.reserve(pk::MAX_ENTITIES);
                }                
                this->registerSystem<pk::sprite_t, pk::SpriteSystem>();                
                this->registerSystem<pk::obstacle_t, pk::ObstacleSystem>();
                for (auto& pair : this->systemMap) {
                    pair.second->entities.reserve(pk::MAX_ENTITIES);
                }
                assert(this->systemMap.size() == pk::NUM_COMPONENTS - 1);
            }            

            template<typename T>
            void insert(const pk::entity_t e) {
                const pk::component_t id = pk::getId<T>();
                this->systemMap[id]->entities.insert(e);
                this->systemByEntity[e].insert(id);
            }
            
            template<typename T>
            void erase(const pk::entity_t e) {
                const pk::component_t id = pk::getId<T>();
                this->systemMap[id]->entities.erase(e);
                this->systemByEntity[e].erase(id);
            }

            template<typename T, typename S>
            const S* getSystem() {
                const pk::component_t id = pk::getId<T>();
                return dynamic_cast<const S*>(this->systemMap[id].get());
            }

            template<typename T>
            const std::unordered_set<pk::entity_t>& getSystemEntities() {
                const pk::component_t id = pk::getId<T>();
                return this->systemMap[id]->entities;
            }

            void update(const float dt) {
                for (const pk::component_t id : this->systemOrder) {
                    this->systemMap[id]->update(dt);
                }
            }

            void draw(const pk::entity_t e) {
                for (const pk::component_t id : this->systemByEntity[e]) {
                    this->systemMap[id]->draw(e);
                }
            }

            void entityDestroy(const pk::entity_t e) override {
                for (auto& pair : this->systemMap) {
                    pair.second->entities.erase(e);
                }
            }   

            void clear() override {
                for (auto& pair : this->systemMap) {
                    pair.second->entities.clear();
                }
            }            

            std::size_t size() const override {
                std::size_t s = 0;
                for (auto& pair : this->systemMap) {
                    s += pair.second->entities.size();
                }
                return s;
            }   

    };
    
} // namespace pk

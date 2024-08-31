#pragma once
#include <unordered_map>
#include "System.hpp"
#include <memory>
#include <iostream>
#include "../constants.hpp"
#include "../TypeId.hpp"


namespace pk {

    class SystemManager {

        private:
            std::unordered_map<pk::component_t, std::unique_ptr<pk::System>> systemMap{};
            std::unordered_map<pk::entity_t, std::unordered_set<pk::component_t>> systemByEntity{};
        
        public:
            SystemManager() {
                for (pk::entity_t e = 0; e < pk::MAX_ENTITIES; e++) {
                    this->systemByEntity.insert({e, {}});                    
                }
            }

            template<typename T, typename S>
            void registerComponent() {
                const pk::component_t id = pk::gTypeId.get<T>();
                this->systemMap.emplace(id, std::make_unique<S>());
                this->systemMap[id]->entities.reserve(pk::MAX_ENTITIES);
            }

            template<typename T>
            void insert(const pk::entity_t e) {
                const pk::component_t id = pk::gTypeId.get<T>();
                if (this->systemMap.find(id) != this->systemMap.end()) {
                    this->systemMap[id]->entities.insert(e);
                    this->systemByEntity[e].insert(id);                    
                }
            }

            template<typename T>
            void erase(const pk::entity_t e) {
                const pk::component_t id = pk::gTypeId.get<T>();
                if (this->systemMap.find(id) != this->systemMap.end()) {
                    this->systemMap[id]->entities.erase(e);
                    this->systemByEntity[e].erase(id);
                }
            }

            template<typename T, typename S>
            const S* getSystem() const {
                const pk::component_t id = pk::gTypeId.get<T>();
                this->systemMap.at(id).get();
            }

            void update(const float dt) {
                for (auto& pair : this->systemMap) {
                    pair.second->update(dt);
                }
            }

            void draw(sf::RenderWindow& window, const std::vector<std::pair<float, pk::entity_t>>& entities) {
                for (const std::pair<float, pk::entity_t>& pair : entities) {
                    for (const pk::component_t id : this->systemByEntity[pair.second]) {
                        this->systemMap[id]->draw(window, pair.second);
                    }
                }
            }

            void clear() {
                for (auto& pair : this->systemMap) {
                    pair.second->entities.clear();
                }
                for (auto& pair : this->systemByEntity) {
                    pair.second.clear();
                }
            }

            void entityDestroy(const pk::entity_t e) {
                for (auto& pair : this->systemMap) {
                    pair.second->entities.erase(e);
                }
                this->systemByEntity[e].clear();
            }

            std::size_t componentSystemCount() const {
                return this->systemMap.size();
            }
        
    };
    
} // namespace pk

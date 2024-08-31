#pragma once
#include "ComponentArray.hpp"
#include <memory>
#include "../TypeId.hpp"


namespace pk {

    class ComponentManager {

        private:
            std::unordered_map<pk::component_t, std::unique_ptr<pk::IComponentArray>> componentMap{};
        
        public:
            template<typename T>
            void registerComponent() {
                this->componentMap.emplace(pk::gTypeId.get<T>(), std::make_unique<pk::ComponentArray<T>>());
            }

            template<typename T>
            T& at(const pk::entity_t e) {
                const pk::component_t id = pk::gTypeId.get<T>();
                pk::ComponentArray<T>* arr = dynamic_cast<pk::ComponentArray<T>*>(this->componentMap[id].get());
                return arr->at(e);
            }

            template<typename T>
            void erase(const pk::entity_t e) {
                const pk::component_t id = pk::gTypeId.get<T>();
                this->componentMap[id]->erase(e);                
            }

            template<typename T>
            void insert(const pk::entity_t e, T c) {
                const pk::component_t id = pk::gTypeId.get<T>();
                pk::ComponentArray<T>* arr = dynamic_cast<pk::ComponentArray<T>*>(this->componentMap[id].get());
                arr->insert(e, std::move(c));
            }

            void clear() {
                for (auto& pair : this->componentMap) {
                    pair.second->clear();
                }
            }

            void entityDestroy(const pk::entity_t e) {
                for (auto& pair : this->componentMap) {
                    pair.second->erase(e);
                }
            }

            std::size_t componentArrayCount() const {
                return this->componentMap.size();
            }

            std::size_t activeComponentsCount() const {
                std::size_t s = 0;
                for (auto& pair : this->componentMap) {
                    s += pair.second->size();
                }
                return s;
            }

    };
    
} // namespace pk

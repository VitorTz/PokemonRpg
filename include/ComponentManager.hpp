#pragma once
#include "ComponentArray.hpp"
#include "EcsManager.hpp"
#include "ComponentId.hpp"
#include "components.hpp"
#include <memory>


namespace pk {


    class ComponentManager : public pk::EcsManager {

        private:
            std::unordered_map<pk::component_t, std::unique_ptr<pk::IComponentArray>> componentMap{};

        private:
            template<typename T>
            void registerComponentArray() {
                const pk::component_t id = pk::getId<T>();
                assert(
                    this->componentMap.find(id) == this->componentMap.end() &&
                    "(ComponentManager) ComponentArray already registered"
                );
                this->componentMap.emplace(id, std::make_unique<pk::ComponentArray<T>>());
            }
    
        public:
            ComponentManager() {
                this->componentMap.reserve(pk::NUM_COMPONENTS);
                this->registerComponentArray<pk::transform_t>();
                this->registerComponentArray<pk::sprite_t>();
                this->registerComponentArray<pk::obstacle_t>();                
                assert(this->componentMap.size() == pk::NUM_COMPONENTS);
            }

            template<typename T>
            void insert(const pk::entity_t e, T c) {
                const pk::component_t id = pk::getId<T>();
                dynamic_cast<pk::ComponentArray<T>*>(this->componentMap[id].get())->insert(e, std::move(c));
            }

            template<typename T>
            void erase(const pk::entity_t e) {
                const pk::component_t id = pk::getId<T>();
                this->componentMap[id]->erase(e);
            }

            template<typename T>
            T& at(const pk::entity_t e) {
                const pk::component_t id = pk::getId<T>();
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

            std::size_t size() const {
                std::size_t s = 0;
                for (auto& pair : this->componentMap) {
                    s += pair.second->size();
                }
                return s;
            }

    };
    
} // namespace pk

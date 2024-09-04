#pragma once
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"
#include "components.hpp"
#include "Camera.hpp"
#include "../util.hpp"


namespace pk {

    class ECS {

        private:
            pk::EntityManager entity{};
            pk::ComponentManager component{};
            pk::SystemManager system{};
        
        private:
            std::queue<pk::entity_t> entitiesToDestroy{};
            bool shouldDestroyAllEntities{};
        
        public:
            void init() {
                std::cout << "[Registrando componentes]\n";
                    pk::gTypeId.registerId<pk::transform_t>();
                    pk::gTypeId.registerId<pk::sprite_t>();
                    pk::gTypeId.registerId<pk::collision_body_t>();
                    pk::gTypeId.registerId<pk::collision_body_static_t>();
                    pk::mAssert(pk::gTypeId.size(), "[INVALID REGISTERED COMPONENT NUM]");
                std::cout << "[Componens registrados]\n";

                std::cout << "[Registrando ComponentArray]\n";
                    this->component.registerComponent<pk::transform_t>();
                    this->component.registerComponent<pk::sprite_t>();
                    this->component.registerComponent<pk::collision_body_t>();
                    this->component.registerComponent<pk::collision_body_static_t>();
                    pk::mAssert(this->component.componentArrayCount() == pk::NUM_COMPONENTS, "[INVALID COMPONENT ARRAY NUM]");
                std::cout << "[ComponentArray registrados]\n";

                std::cout << "[Registrando System]\n";
                    this->system.registerComponent<pk::sprite_t, pk::SpriteSystem>();
                    this->system.registerComponent<pk::collision_body_t, pk::CollisionBodySystem>();
                    this->system.registerComponent<pk::collision_body_static_t, pk::CollisionBodyStaticSystem>();
                    pk::mAssert(this->system.componentSystemCount() == pk::NUM_COMPONENTS - 1, "[INVALID COMPONENT SYSTEM NUM]");
                std::cout << "[System registrados]\n";
            }

            pk::entity_t entityCreate(const pk::zindex_t zindex, const bool isOnCamera) {
                const pk::entity_t e = this->entity.entityCreate();
                this->component.insert<pk::transform_t>(e, pk::transform_t{zindex});
                if (isOnCamera) pk::gCamera.insert(e);
                return e;
            }

            void entityDestroy(const pk::entity_t e) {
                this->entitiesToDestroy.push(e);
            }

            void clear() {
                this->shouldDestroyAllEntities = true;
            }

            template<typename T>
            T& getComponent(const pk::entity_t e) {
                return this->component.at<T>(e);
            }

            template<typename T>
            void insertComponent(const pk::entity_t e, T c) {
                this->component.insert<T>(e, std::move(c));
                this->system.insert<T>(e);
            }

            template<typename T>
            void eraseComponent(const pk::entity_t e) {
                this->component.erase<T>(e);
                this->system.erase<T>(e);
            }

            template<typename T>
            void insertToSystem(const pk::entity_t e) {
                this->system.insert<T>(e);
            }

            template<typename T>
            void eraseFromSystem(const pk::entity_t e) {
                this->system.erase<T>(e);
            }

            void createSprite(const pk::entity_t e, const char* filePath) {
                this->insertComponent<pk::sprite_t>(e, pk::sprite_t{filePath});                
                pk::sprite_t& s = this->component.at<pk::sprite_t>(e);
                pk::transform_t& t = this->component.at<pk::transform_t>(e);
                t.size = (sf::Vector2f) s.sfSprite.getTexture()->getSize();
            }                     

            void update(const float dt) {
                this->system.update(dt);

                if (this->shouldDestroyAllEntities) {
                    this->shouldDestroyAllEntities = false;
                    this->entitiesToDestroy = std::queue<pk::entity_t>();
                    pk::gCamera.clear();
                    this->entity.clear();
                    this->component.clear();
                    this->system.clear();                    
                }

                while (this->entitiesToDestroy.empty() == false) {
                    const pk::entity_t e = this->entitiesToDestroy.front();
                    this->entitiesToDestroy.pop();
                    pk::gCamera.erase(e);
                    this->entity.entityDestroy(e);
                    this->component.entityDestroy(e);
                    this->system.entityDestroy(e);
                }
            }

            void draw(sf::RenderWindow& window, const pk::entity_t e) {
                this->system.draw(window, e);
            }

            void draw(
                sf::RenderWindow& window,
                const std::vector<std::pair<float, pk::entity_t>>& entities
            ) {
                this->system.draw(window, entities);
            }

    };

    inline pk::ECS gEcs{};
    
} // namespace pk

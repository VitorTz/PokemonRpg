#pragma once
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "Camera.hpp"
#include "SystemManager.hpp"
#include <stdio.h>


namespace pk {

    class ECS {

        private:
            std::unique_ptr<pk::EntityManager> entityManager{};
            std::shared_ptr<pk::ComponentManager> componentManager{};            
            std::shared_ptr<pk::SystemManager> systemManager{};
        
        private:
            std::queue<pk::entity_t> entitiesToDestroy{};
            bool shouldDestroyAllEntities{};

        public:
            
            void init() {
                pk::registerComponent<pk::transform_t>();
                pk::registerComponent<pk::sprite_t>();                
                pk::registerComponent<pk::obstacle_t>();
                assert(pk::gComponentIdMap.size() == pk::NUM_COMPONENTS);

                this->entityManager = std::make_unique<pk::EntityManager>();
                this->systemManager = std::make_shared<pk::SystemManager>();
                this->componentManager = std::make_shared<pk::ComponentManager>();
                pk::gCamera.init(this->systemManager, this->componentManager);
            }

            pk::entity_t createEntity(const pk::zindex_t zindex, const bool isOnCamera) {
                const pk::entity_t e = this->entityManager->entityCreate();
                if (isOnCamera) { pk::gCamera.insert(e, zindex); }
                this->componentManager->insert<pk::transform_t>(e, pk::transform_t{.zindex = zindex});
                return e;
            }

            template<typename T>
            void addComponent(const pk::entity_t e, T c) {
                this->componentManager->insert<T>(e, std::move(c));
                this->systemManager->insert<T>(e);
            }

            template<typename T>
            void rmvComponent(const pk::entity_t e) {
                this->componentManager->erase<T>(e);
                this->systemManager->erase<T>(e);
            }

            template<typename T>
            T& getComponent(const pk::entity_t e) {
                return this->componentManager->at<T>(e);
            }

            template<typename T>
            void addToSystem(const pk::entity_t e) {
                this->systemManager->insert<T>(e);
            }

            template<typename T>
            void rmvFromSystem(const pk::entity_t e) {                
                this->systemManager->erase<T>(e);
            }

            pk::entity_t createSprite(const char* fileName, const pk::zindex_t zindex) {
                const pk::entity_t e = this->createEntity(zindex, true);
                this->addSprite(e, fileName);
                return e;
            }

            void addSprite(const pk::entity_t e, const char* fileName) {
                this->addComponent<pk::sprite_t>(e, pk::sprite_t{fileName});
                const pk::sprite_t& sprite = this->componentManager->at<pk::sprite_t>(e);
                this->componentManager->at<pk::transform_t>(e).size = {
                    static_cast<float>(sprite.texture.width),
                    static_cast<float>(sprite.texture.height)
                };
            }                        

            void entityDestroy(const pk::entity_t e) {
                this->entitiesToDestroy.push(e);
            }

            std::pair<pk::entity_t, bool> checkCollision(const Rectangle rect) {
                std::pair<pk::entity_t, bool> result{0, false};                
                for (const pk::entity_t e : this->systemManager->getSystemEntities<pk::obstacle_t>()) {
                    const pk::obstacle_t& obstacle = this->componentManager->at<pk::obstacle_t>(e);    
                    if (CheckCollisionRecs(rect, obstacle.rect)) {
                        result.first = e;
                        result.second = true;
                        break;
                    }
                }
                return result;
            }

            void clear() {
                this->shouldDestroyAllEntities = true;
            }            

            void update(const float dt) {
                this->systemManager->update(dt);

                if (this->shouldDestroyAllEntities) {
                    this->shouldDestroyAllEntities = false;
                    this->entitiesToDestroy = std::queue<pk::entity_t>();
                    pk::gCamera.clear();
                    this->entityManager->clear();
                    this->componentManager->clear();
                    this->systemManager->clear();                    
                }

                while (this->entitiesToDestroy.empty() == false) {
                    const pk::entity_t e = this->entitiesToDestroy.front();
                    this->entitiesToDestroy.pop();
                    pk::gCamera.erase(e);
                    this->entityManager->entityDestroy(e);
                    this->componentManager->entityDestroy(e);
                    this->systemManager->entityDestroy(e);
                }
            }

            void draw() {
                pk::gCamera.draw();
            }

            std::size_t getNumEntities() const {
                return this->entityManager->size();
            }

            std::size_t getNumComponents() const {
                return this->componentManager->size();
            }

            std::size_t getNumSystemSize() const {
                return this->systemManager->size();
            }

    };

    inline pk::ECS gEcs{};
    
} // namespace pk
 
//
// Created by vitor on 9/14/24.
//

#ifndef ECS_H
#define ECS_H
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SysteManager.h"
#include "../Camera.h"

namespace pk {

    class ECS {

    private:
        std::unique_ptr<pk::EntityManager> entity{};
        std::unique_ptr<pk::ComponentManager> component{};
        std::unique_ptr<pk::SystemManager> system{};

    private:
        std::queue<pk::entity_t> entitiesToDestroy{};
        bool shouldDestroyAllEntities{};

    public:
        void init() {
            this->entity = std::make_unique<pk::EntityManager>();
            this->component = std::make_unique<pk::ComponentManager>();
            this->system = std::make_unique<pk::SystemManager>();
        }

        pk::entity_t entityCreate(const pk::zindex_t zindex, const bool onCamera) {
            const pk::entity_t e = this->entity->entityCreate();
            this->component->insert<pk::transform_t>(e, pk::transform_t{zindex});
            if (onCamera) pk::gCamera.insert(e);
            return e;
        }

        void entityDestroy(const pk::entity_t e) {
            this->entitiesToDestroy.push(e);
        }

        template<typename T>
        void insertComponent(const pk::entity_t e, T c) {
            this->component->insert<T>(e, std::move(c));
            this->system->insert<T>(e);
        }

        template<typename T>
        void eraseComponent(const pk::entity_t e) {
            this->component->erase<T>(e);
            this->system->erase<T>(e);
        }

        template<typename T>
        T& getComponent(const pk::entity_t e) {
            return this->component->at<T>(e);
        }

        pk::transform_t& getTransform(const pk::entity_t e) {
            return this->component->getTransform(e);
        }

        void update(const float dt) {
            this->system->update(dt);

            if (this->shouldDestroyAllEntities) {
                this->shouldDestroyAllEntities = false;
                pk::gCamera.clear();
                this->entity->clear();
                this->component->clear();
                this->system->clear();
                this->entitiesToDestroy = std::queue<pk::entity_t>();
            }

            while (this->entitiesToDestroy.empty() == false) {
                const pk::entity_t e = this->entitiesToDestroy.front();
                this->entitiesToDestroy.pop();
                pk::gCamera.erase(e);
                this->entity->entityDestroy(e);
                this->component->entityDestroy(e);
                this->system->entityDestroy(e);
            }
        }

        void draw(sf::RenderWindow& window) {
            pk::gCamera.draw(window, this->system.get());
        }

        void clear() {
            this->shouldDestroyAllEntities = true;
        }

    };

    inline pk::ECS gEcs{};

}

#endif //ECS_H

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

        std::pair<bool, pk::entity_t> checkCollision(const sf::FloatRect& rect) const {
            std::pair<bool, pk::entity_t> r{false, 0};
            const std::unordered_set<pk::entity_t>& ent1 = this->system->getEntitiesFromSystem<pk::collision_box_t>();
            const std::unordered_set<pk::entity_t>& ent2 = this->system->getEntitiesFromSystem<pk::collision_box_static_t>();
            // collision_box_t
                for (const pk::entity_t e : ent1) {
                    const pk::collision_box_t& c = this->component->at<pk::collision_box_t>(e);
                    if (c.rect.intersects(rect)) {
                        r.first = true;
                        r.second = e;
                        break;
                    }
                }

            // collision_box_static_t
                if (r.first == false) {
                    for (const pk::entity_t e : ent2) {
                        const pk::collision_box_static_t& c = this->component->at<pk::collision_box_static_t>(e);
                        if (c.rect.intersects(rect)) {
                            r.first = true;
                            r.second = e;
                            break;
                        }
                    }
                }
            return r;
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

        void draw(sf::RenderWindow& window) const {
            pk::gCamera.draw(window, this->system.get());
        }

        void clear() {
            this->shouldDestroyAllEntities = true;
        }

        const pk::EntityManager* getEntityManager() const {
            return this->entity.get();
        }

        const pk::ComponentManager* getComponentManager() const {
            return this->component.get();
        }

        const pk::SystemManager* getSystemManager() const {
            return this->system.get();
        }

    };

    inline pk::ECS gEcs{};

}

#endif //ECS_H

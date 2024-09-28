//
// Created by vitor on 9/28/24.
//

#ifndef ECS_H
#define ECS_H
#include <algorithm>
#include <map>
#include "Component.h"
#include "components.h"
#include "ECS.h"
#include "Entity.h"
#include "System.h"
#include "Camera.h"


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
        ECS() {
            this->entity = std::make_unique<pk::EntityManager>();
            this->component = std::make_unique<pk::ComponentManager>();
            this->system = std::make_unique<pk::SystemManager>();
        }

        void init() {
            pk::gTypeId.registerType<pk::transform_t>();
            pk::gTypeId.registerType<pk::sprite_t>();
            pk::gTypeId.registerType<pk::sprite_animation_t>();
            pk::gTypeId.registerType<pk::collision_t>();
            pk::gTypeId.registerType<pk::movement_t>();
            pk::gTypeId.registerType<pk::player_t>();
            assert(pk::gTypeId.size() == pk::NUM_COMPONENTS);

            this->component->registerComponent<pk::transform_t>();
            this->component->registerComponent<pk::sprite_t>();
            this->component->registerComponent<pk::sprite_animation_t>();
            this->component->registerComponent<pk::collision_t>();
            this->component->registerComponent<pk::movement_t>();
            this->component->registerComponent<pk::player_t>();
            assert(this->component->size() == pk::NUM_COMPONENTS);

            this->system->registerSystem<pk::transform_t, pk::TransformSystem>();
            this->system->registerSystem<pk::sprite_t, pk::SpriteSystem>();
            this->system->registerSystem<pk::sprite_animation_t, pk::SpriteAnimationSystem>();
            this->system->registerSystem<pk::collision_t, pk::CollisionSystem>();
            this->system->registerSystem<pk::movement_t, pk::MovementSystem>();
            this->system->registerSystem<pk::player_t, pk::PlayerSystem>();
            assert(this->system->size() == pk::NUM_COMPONENTS);
        }

        pk::entity_t entityCreate(const pk::zindex_t zindex, const bool submitToCamera) {
            assert(zindex >= pk::CAMERA_MIN_ZINDEX && zindex <= pk::CAMERA_MAX_ZINDEX);
            const pk::entity_t e = this->entity->entityCreate();
            this->addComponent<pk::transform_t>(e, pk::transform_t{zindex});
            if (submitToCamera) pk::gCamera.insert(e);
            return e;
        }

        void entityDestroy(const pk::entity_t e) {
            this->entitiesToDestroy.push(e);
        }

        template<typename T>
        T& getComponent(const pk::entity_t e) {
            return this->component->at<T>(e);
        }

        template<typename T>
        void addComponent(const pk::entity_t e, T c) {
            this->component->insert<T>(e, std::move(c));
            this->system->insert<T>(e);
        }

        pk::transform_t& getTransform(const pk::entity_t e) {
            return this->component->at<pk::transform_t>(e);
        }

        void update(const float dt) {
            this->system->update(dt);

            if (this->shouldDestroyAllEntities) {
                this->shouldDestroyAllEntities = false;
                pk::gCamera.clear();
                this->entitiesToDestroy = std::queue<pk::entity_t>();
                this->entity->clear();
                this->component->clear();
                this->system->clear();
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

        void draw() const {
            pk::gCamera.draw(this->system.get());
        }

        bool checkCollision(const Rectangle& rect) const {
            pk::ComponentArray<pk::collision_t>* cArray = this->component->getComponentArray<pk::collision_t>();
            return std::any_of(
                cArray->begin(),
                cArray->end(),
                [rect](const pk::collision_t& c) {
                    return CheckCollisionRecs(c.rect, rect);
                });
        }

        void clear() {
            this->shouldDestroyAllEntities = true;
        }

    };

    inline pk::ECS gEcs{};

}

#endif //ECS_H

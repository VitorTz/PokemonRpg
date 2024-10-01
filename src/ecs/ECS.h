//
// Created by vitor on 9/30/24.
//

#ifndef ECS_H
#define ECS_H
#include "Entity.h"
#include "Component.h"
#include "System.h"
#include "../util/TiledMap.h"


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

        pk::entity_t entityCreate(const pk::zindex_t zindex, const bool isOnCamera) {
            const pk::entity_t e = this->entity->entityCreate();
            this->component->insert<pk::transform_t, pk::id::transform>(e, pk::transform_t{zindex});
            if (isOnCamera) this->system->addToCamera(e);
            return e;
        }

        pk::entity_t createSprite(const pk::zindex_t zindex, const char* fileName) {
            const pk::entity_t e = this->entityCreate(zindex, true);
            this->addComponent<pk::sprite_t, pk::id::sprite>(e, pk::sprite_t{fileName});
            const pk::sprite_t& sprite = this->component->at<pk::sprite_t, pk::id::sprite>(e);
            pk::transform_t& transform = this->getTransform(e);
            transform.size = Vector2{
                static_cast<float>(sprite.texture.width),
                static_cast<float>(sprite.texture.height)
            };
            return e;
        }

        pk::entity_t createPlayer() {
            const pk::entity_t playerEntity = this->entityCreate(pk::PLAYER_ZINDEX, true);
            const pk::entity_t shadowEntity = this->createSprite(pk::PLAYER_SHADOW_ZINDEX, GRAPHICS_PATH "other/shadow.png");
            this->addComponent<pk::player_t, id::player>(playerEntity, pk::player_t{shadowEntity});
            this->addComponent<pk::sprite_animation_t, id::sprite_animation>(playerEntity, pk::sprite_animation_t{pk::PLAYER_SPRITE_ANIMATION});
            this->addComponent<pk::movement_t, id::movement>(playerEntity, pk::movement_t{});
            return playerEntity;
        }

        template<typename T, pk::component_t id>
        void addComponent(const pk::entity_t e, T c) {
            this->component->insert<T, id>(e, std::move(c));
            this->system->insert(e, id);
        }

        template<typename T, pk::component_t id>
        T& getComponent(const pk::entity_t e) {
            return this->component->at<T, id>(e);
        }

        pk::transform_t& getTransform(const pk::entity_t e) {
            return this->component->at<pk::transform_t, pk::id::transform>(e);
        }

        void  entityDestroy(const pk::entity_t e) {
            this->entitiesToDestroy.push(e);
        }

        void update(const float dt) {
            this->system->update(dt);

            if (this->shouldDestroyAllEntities) {
                this->shouldDestroyAllEntities = false;
                this->unloadAllEntities();
            }

            while (this->entitiesToDestroy.empty() == false) {
                const pk::entity_t e = this->entitiesToDestroy.front();
                this->entitiesToDestroy.pop();
                this->system->rmvFromCamera(e);
                this->entity->entityDestroy(e);
                this->component->entityDestroy(e);
                this->system->entityDestroy(e);
            }
        }

        void draw() const {
            this->system->draw();
        }

        void unloadAllEntities() {
            this->entity->clear();
            this->component->clear();
            this->system->clear();
            this->entitiesToDestroy = std::queue<pk::entity_t>();
        }

        void clear() {
            this->shouldDestroyAllEntities = true;
        }

    };

    inline pk::ECS gEcs{};


}

#endif //ECS_H

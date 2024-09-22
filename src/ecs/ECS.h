//
// Created by vitor on 9/21/24.
//

#ifndef ECS_H
#define ECS_H
#include "../util/Camera.h"
#include "Entity.h"
#include "Component.h"
#include "System.h"


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
            pk::gTypeId.registerType<pk::transform_t>();
            pk::gTypeId.registerType<pk::sprite_t>();
            pk::gTypeId.registerType<pk::sprite_animation_t>();
            pk::gTypeId.registerType<pk::movement_t>();
            pk::gTypeId.registerType<pk::collision_t>();
            pk::gTypeId.registerType<pk::player_t>();
            assert(pk::gTypeId.size() == pk::NUM_COMPONENTS);
            this->entity = std::make_unique<pk::EntityManager>();
            this->component = std::make_unique<pk::ComponentManager>();
            this->system = std::make_unique<pk::SystemManager>();
        }

        pk::entity_t entityCreate(
            const pk::zindex_t zindex,
            const bool isOnCamera,
            const sf::Vector2f& pos = sf::Vector2f(0.0f, 0.0f)
        ) {
            const pk::entity_t e = this->entity->entityCreate();
            this->component->insert(e, pk::transform_t{pos, zindex});
            if (isOnCamera) pk::gCamera.insert(e);
            return e;
        }

        void entityDestroy(const pk::entity_t e) {
            this->entitiesToDestroy.push(e);
        }

        template<typename T>
        void addComponent(const pk::entity_t e, T c) {
            this->component->insert<T>(e, std::move(c));
            this->system->insert<T>(e);
        }

        template<typename T>
        void rmvComponent(const pk::entity_t e) {
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
            if (this->shouldDestroyAllEntities == true) {
                this->shouldDestroyAllEntities = false;
                this->entity->clear();
                this->component->clear();
                this->system->clear();
                this->entitiesToDestroy = std::queue<pk::entity_t>();
            }
            while (this->entitiesToDestroy.empty() == false) {
                const pk::entity_t e = this->entitiesToDestroy.front();
                this->entitiesToDestroy.pop();
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

        pk::entity_t createSpriteEntity(
            const pk::zindex_t zindex,
            const char* spriteFilePath,
            const sf::Vector2f& pos
        ) {
            const pk::entity_t e = this->entityCreate(zindex, true);
            this->addComponent<pk::sprite_t>(e, pk::sprite_t{spriteFilePath});
            const pk::sprite_t& sprite = this->component->at<pk::sprite_t>(e);
            pk::transform_t& transform = this->component->getTransform(e);
            transform.size = static_cast<sf::Vector2f>(sprite.spr.getTexture()->getSize());
            transform.pos = pos;
            return e;
        }

        pk::entity_t createSpriteAnimationEntity(
            const pk::zindex_t zindex,
            const pk::sprite_animation_source_t& source,
            const sf::Vector2f& pos
        ) {
            const pk::entity_t e = this->entityCreate(zindex, true);
            this->addComponent<pk::sprite_animation_t>(e, pk::sprite_animation_t{source});
            pk::transform_t& transform = this->component->getTransform(e);
            transform.pos = pos;
            transform.size.x = static_cast<float>(source.spriteWidth);
            transform.size.y = static_cast<float>(source.spriteHeight);
            return e;
        }

        pk::entity_t createCollisionSpriteEntity(
            const pk::zindex_t zindex,
            const char* spriteFilePath,
            const sf::Vector2f& pos,
            const sf::Vector2f collisionBoxScale = sf::Vector2f(1.0f, 1.0f)
        ) {
            const pk::entity_t e = this->createSpriteEntity(zindex, spriteFilePath, pos);
            const pk::transform_t& transform = this->component->getTransform(e);
            const float width = transform.size.x * collisionBoxScale.x;
            const float height = transform.size.y * collisionBoxScale.y;
            this->addComponent<pk::collision_t>(
                e, pk::collision_t{
                    sf::FloatRect(
                        transform.pos.x - width / 2.0f,
                        transform.pos.y - height / 2.0f,
                        width,
                        height
                    )
                }
            );
            return e;
        }

        pk::entity_t createCollision(const float x, const float y, const float width, const float height) {
            const pk::entity_t e = this->entityCreate(0, false, sf::Vector2f(x, y));
            this->component->getTransform(e).size = sf::Vector2f(width, height);
            this->addComponent<pk::collision_t>(e, pk::collision_t{sf::FloatRect(x, y, width, height)});
            return e;
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

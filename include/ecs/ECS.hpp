#pragma once
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"
#include "components.hpp"
#include "../util.hpp"


namespace pk {

    class ECS {

        private:
            pk::EntityManager entity{};
            pk::ComponentManager component{};
            pk::SystemManager system{};
        
        private:
            std::array<bool, pk::MAX_ENTITIES> onCamera{};
            pk::Camera camera{};
        
        private:
            std::queue<pk::entity_t> entitiesToDestroy{};
            bool shouldDestroyAllEntities{};
        
        public:
            void init() {
                for (pk::zindex_t zindex = pk::ZINDEX_MIN; zindex <= pk::ZINDEX_MAX; zindex++) {
                    this->camera.insert({zindex, {}});
                    this->camera[zindex].reserve(pk::MAX_ENTITIES);
                }
                pk::gTypeId.registerId<pk::transform_t>();
                pk::gTypeId.registerId<pk::sprite_t>();
                pk::gTypeId.registerId<pk::collision_body_t>();
                pk::gTypeId.registerId<pk::collision_body_static_t>();
                pk::mAssert(pk::gTypeId.size(), "[INVALID REGISTERED COMPONENT NUM]");

                this->component.registerComponent<pk::transform_t>();
                this->component.registerComponent<pk::sprite_t>();
                this->component.registerComponent<pk::collision_body_t>();
                this->component.registerComponent<pk::collision_body_static_t>();
                pk::mAssert(this->component.componentArrayCount() == pk::NUM_COMPONENTS, "[INVALID COMPONENT ARRAY NUM]");

                this->system.registerComponent<pk::sprite_t, pk::SpriteSystem>();
                this->system.registerComponent<pk::collision_body_t, pk::CollisionBodySystem>();
                this->system.registerComponent<pk::collision_body_static_t, pk::CollisionBodyStaticSystem>();
                pk::mAssert(this->system.componentSystemCount() == pk::NUM_COMPONENTS - 1, "[INVALID COMPONENT SYSTEM NUM]");
            }

            pk::entity_t entityCreate(const pk::zindex_t zindex, const bool isOnCamera) {
                const pk::entity_t e = this->entity.entityCreate();
                this->component.insert<pk::transform_t>(e, pk::transform_t{zindex});            
                return e;
            }

            void entityDestroy(const pk::entity_t e) {
                this->entitiesToDestroy.push(e);
            }

            void submitToCamera(const pk::entity_t e) {
                const pk::zindex_t zindex = this->component.at<pk::transform_t>(e).zindex;
                if (this->onCamera[e] == false) {
                    this->onCamera[e] = true;
                    this->camera[zindex].push_back({0.0f, e});
                }
            }


    };
    
} // namespace pk

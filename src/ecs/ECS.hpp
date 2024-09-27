#pragma once
#include <array>
#include <cassert>
#include <map>
#include <queue>
#include <vector>
#include "Entity.hpp"
#include "Component.hpp"
#include "System.hpp"
#include "../util/Camera.hpp"


namespace pk {


    class ECS {

        private:
            pk::EntityManager entity{};
            pk::ComponentManager component{};
            pk::SystemManager system{};
        
        private:
            std::map<pk::zindex_t, std::vector<std::pair<float, pk::entity_t>>> cameraEntities{};
            std::array<bool, pk::MAX_ENTITIES> onCamera{};

        private:
            std::queue<pk::entity_t> entitiesToDestroy{};
            bool shouldDestroyAllEntities{};

        private:
            template<typename T, typename S>
            void registerComponent() {
                pk::gTypeId.registerType<pk::transform_t>();
                this->component.registerComponent<pk::transform_t>();
                this->system.registerSystem<pk::transform_t, S>();
            }

        public:

            void init() {
                this->registerComponent<pk::transform_t, pk::TransformSystem>();
                this->registerComponent<pk::sprite_t, pk::SpriteSystem>();
                this->registerComponent<pk::sprite_animation_t, pk::SpriteAnimationSystem>();
                this->registerComponent<pk::collision_t, pk::CollisionSystem>();
                this->registerComponent<pk::player_t, pk::PlayerSystem>();
                assert(pk::gTypeId.size() == pk::NUM_COMPONENTS);
                assert(this->component.numComponentArray() == pk::NUM_COMPONENTS);                
                assert(this->system.numSystem() == pk::NUM_COMPONENTS);
            }
            
            pk::entity_t entityCreate(const pk::zindex_t zindex, const bool isOnCamera) {
                const pk::entity_t e = this->entity.entityCreate();
                this->component.insert(e, pk::transform_t{zindex});
                if (isOnCamera) pk::gCamera.insert(e);
                return e;
            }

            void entityDestroy(const pk::entity_t e) {
                this->entitiesToDestroy.push(e);
            }

            template<typename T>
            void addComponent(const pk::entity_t e, T c) {
                this->component.insert<T>(e, std::move(c));
                this->system.insert<T>(e);
            }

            template<typename T>
            T& getComponent(const pk::entity_t e) {
                return this->component.at<T>(e);
            }            

            inline pk::transform_t& getTransform(const pk::entity_t e) {
                return this->component.at<pk::transform_t>(e);
            }

            void clear() {
                this->shouldDestroyAllEntities = true;
            }

            void update(const float dt) {
                this->system.update(dt);
                if (this->shouldDestroyAllEntities) {
                    this->shouldDestroyAllEntities = false;
                    
                }
            }

            void draw() {
                pk::gCamera.sortEntitiesByCenterYpos();
                const std::map<pk::zindex_t, std::vector<std::pair<float, pk::entity_t>>>& cameraEntities = pk::gCamera.getEntities();                
                for (const auto& pair : cameraEntities) {
                    this->system.draw(pair.second);
                }                
            }

    };

    inline pk::ECS gEcs{};

}


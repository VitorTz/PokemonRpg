//
// Created by vitor on 9/21/24.
//

#ifndef SYSTEM_H
#define SYSTEM_H
#include "components.h"
#include "../pokemon.h"


namespace pk {

    class System {

    public:
        std::unordered_set<pk::entity_t> entities{};

    public:
        virtual ~System() = default;
        virtual void update(float dt) = 0;
        virtual void render(sf::RenderWindow& window, pk::entity_t e) = 0;

    };


    class SpriteSystem final : public pk::System {

    public:
        void update(float dt) override;
        void render(sf::RenderWindow& window, pk::entity_t e) override;

    };

    class SpriteAnimationSystem final : public pk::System {

    public:
        void update(float dt) override;
        void render(sf::RenderWindow& window, pk::entity_t e) override;

    };


    class PlayerSystem final : public pk::System {

    public:
        void update(float dt) override;
        void render(sf::RenderWindow& window, pk::entity_t e) override;
    };

    class MovementSystem final : public pk::System {

    public:
        void update(float dt) override;
        void render(sf::RenderWindow& window, pk::entity_t e) override;
    };

    class CollisionSystem final : public pk::System {

    public:
        void update(float dt) override;
        void render(sf::RenderWindow& window, pk::entity_t e) override;
    };

    class SystemManager {

    private:
        std::unordered_map<pk::component_t, std::unique_ptr<pk::System>> systemMap{};
        std::unordered_map<pk::entity_t, std::unordered_set<pk::component_t>> systemByEntity{};
        std::vector<pk::component_t> systemUpdateOrder{};

    public:
        SystemManager() {
            for (pk::entity_t e = 0; e < pk::MAX_ENTITIES; e++) {
                this->systemByEntity[e].reserve(pk::NUM_COMPONENTS);
            }
            this->systemMap.emplace(pk::gTypeId.get<pk::sprite_t>(), std::make_unique<pk::SpriteSystem>());
            this->systemMap.emplace(pk::gTypeId.get<pk::sprite_animation_t>(), std::make_unique<pk::SpriteAnimationSystem>());
            this->systemMap.emplace(pk::gTypeId.get<pk::collision_t>(), std::make_unique<pk::CollisionSystem>());
            this->systemMap.emplace(pk::gTypeId.get<pk::movement_t>(), std::make_unique<pk::PlayerSystem>());
            this->systemMap.emplace(pk::gTypeId.get<pk::player_t>(), std::make_unique<pk::PlayerSystem>());
            this->systemUpdateOrder.push_back(pk::gTypeId.get<pk::sprite_animation_t>());
            this->systemUpdateOrder.push_back(pk::gTypeId.get<pk::movement_t>());
            this->systemUpdateOrder.push_back(pk::gTypeId.get<pk::player_t>());
            assert(this->systemMap.size() == pk::NUM_COMPONENTS - 1);
        }

        template<typename T>
        void insert(const pk::entity_t e) {
            const pk::component_t id = pk::gTypeId.get<T>();
            this->systemMap[id]->entities.insert(e);
            this->systemByEntity[e].insert(id);
        }

        template<typename T>
        void erase(const pk::entity_t e) {
            const pk::component_t id = pk::gTypeId.get<T>();
            this->systemMap[id]->entities.erase(e);
            this->systemByEntity[e].erase(id);
        }

        void entityDestroy(const pk::entity_t e) {
            for (auto& pair : this->systemMap) {
                pair.second->entities.erase(e);
            }
            this->systemByEntity[e].clear();
        }

        void update(const float dt) {
            for (const pk::component_t id : this->systemUpdateOrder) {
                this->systemMap[id]->update(dt);
            }
        }

        void draw(sf::RenderWindow& window, const pk::EntityVector& v) {
            for (const std::pair<float, pk::entity_t>& pair : v) {
                for (const pk::component_t systemId : this->systemByEntity[pair.second]) {
                    this->systemMap[systemId]->render(window, pair.second);
                }
            }
        }

        void clear() {
            for (auto& pair : this->systemMap) {
                pair.second->entities.clear();
            }
            for (auto& pair : this->systemByEntity) {
                pair.second.clear();
            }
        }

        std::size_t size() const {
            std::size_t s{};
            for (auto& pair : this->systemMap) {
                s += pair.second->entities.size();
            }
            return s;
        }

    };


}

#endif //SYSTEM_H

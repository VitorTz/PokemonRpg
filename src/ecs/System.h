//
// Created by vitor on 9/28/24.
//

#ifndef SYSTEM_H
#define SYSTEM_H
#include <cassert>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "../util/TypeID.h"
#include "../util/types.h"
#include "../util/constants.h"


namespace pk {


    class System {

    public:
        std::unordered_set<pk::entity_t> entities{};

    public:
        virtual ~System() = default;
        virtual void update(float dt) = 0;
        virtual void draw(pk::entity_t e) = 0;

    };


    class TransformSystem final : public pk::System {

    public:
        void update(float dt) override;
        void draw(pk::entity_t e) override;

    };

    class SpriteSystem final : public pk::System {

    public:
        void update(float dt) override;
        void draw(pk::entity_t e) override;

    };

    class CollisionSystem final : public pk::System {

    public:
        void update(float dt) override;
        void draw(pk::entity_t e) override;

    };


    class MovementSystem final : public pk::System {

    public:
        void update(float dt) override;
        void draw(pk::entity_t e) override;

    };

    class SpriteAnimationSystem final : public pk::System {

    public:
        void update(float dt) override;
        void draw(pk::entity_t e) override;

    };

    class PlayerSystem final : public pk::System {

    public:
        PlayerSystem();
        void update(float dt) override;
        void draw(pk::entity_t e) override;

    };


    class SystemManager {

    private:
        std::unordered_map<pk::component_t, std::unique_ptr<pk::System>> systemMap{};
        std::unordered_map<pk::entity_t, std::unordered_set<pk::component_t>> entityToSystems{};
        std::vector<pk::component_t> systemOrder{};

    public:
        SystemManager() {
            for (pk::entity_t e = 0; e < pk::MAX_ENTITIES; e++) {
                this->entityToSystems[e].reserve(32);
            }
        }
        template<typename T, typename S>
        void registerSystem() {
            const pk::component_t id = pk::gTypeId.get<T>();
            assert(this->systemMap.find(id) == this->systemMap.end());
            this->systemMap.emplace(id, std::make_unique<S>());
        }

        template<typename T>
        void insert(const pk::entity_t e) {
            const pk::component_t id = pk::gTypeId.get<T>();
            this->systemMap[id]->entities.insert(e);
            this->entityToSystems[e].insert(id);
        }

        template<typename T>
        void erase(const pk::entity_t e) {
            const pk::component_t id = pk::gTypeId.get<T>();
            this->systemMap[id]->entities.erase(e);
            this->entityToSystems[e].erase(id);
        }

        void entityDestroy(const pk::entity_t e) {
            for (auto& pair : this->systemMap) {
                pair.second->entities.erase(e);
            }
            this->entityToSystems[e].clear();
        }


        void update(const float dt) {
            for (const pk::component_t id : this->systemOrder) {
                this->systemMap[id]->update(dt);
            }
        }

        template<typename T, typename S>
        const S* getSystem() const {
            const pk::component_t id = pk::gTypeId.get<T>();
            return dynamic_cast<const S*>(this->systemMap.at(id).get());
        }

        template<typename T>
        const std::unordered_set<pk::entity_t>& getSystemEntities() const {
            return this->systemMap.at(pk::gTypeId.get<T>())->entities;
        }

        void draw(const std::vector<std::pair<float, pk::entity_t>>& v) {
            for (const std::pair<float, pk::entity_t>& pair : v) {
                for (const pk::component_t id : this->entityToSystems[pair.second]) {
                    this->systemMap[id]->draw(pair.second);
                }
            }
        }

        void clear() {
            for (auto& pair : this->systemMap) {
                pair.second->entities.clear();
            }
        }

        std::size_t size() const {
            return this->systemMap.size();
        }

    };


}

#endif //SYSTEM_H

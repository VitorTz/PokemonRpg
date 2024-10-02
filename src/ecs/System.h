//
// Created by vitor on 9/30/24.
//

#ifndef SYSTEM_H
#define SYSTEM_H
#include "EcsManager.h"
#include "../pokemon.h"


namespace pk {

    class System {

    protected:
        const pk::TiledMapId mapId;

    public:
        std::unordered_set<pk::entity_t> entities{};

    public:
        explicit System(const pk::TiledMapId mapId) : mapId(mapId) { }
        virtual ~System() = default;
        virtual void update(float dt) = 0;
        virtual void draw(pk::entity_t e) = 0;

    };

    class TransformSystem final : public pk::System {

    public:
        explicit TransformSystem(pk::TiledMapId mapId);
        void update(float dt) override;
        void draw(pk::entity_t e) override;

    };

    class SpriteSystem final : public pk::System {

    public:
        explicit SpriteSystem(pk::TiledMapId mapId);
        void update(float dt) override;
        void draw(pk::entity_t e) override;

    };

    class SpriteAnimationSystem final : public pk::System {

    public:
        explicit SpriteAnimationSystem(pk::TiledMapId mapId);
        void update(float dt) override;
        void draw(pk::entity_t e) override;

    };

    class PlayerSystem final : public pk::System {

    public:
        explicit PlayerSystem(pk::TiledMapId mapId);
        void update(float dt) override;
        void draw(pk::entity_t e) override;

    };

    class SystemManager final : public pk::EcsManager {

    private:
        std::unordered_map<pk::component_t, std::unique_ptr<pk::System>> systemMap{};
        std::unordered_map<pk::entity_t, std::unordered_set<pk::component_t>> entityToComponents{};
        std::vector<pk::component_t> systemOrder{};

    public:
        explicit SystemManager(pk::TiledMapId mapId);
        void insert(pk::entity_t e, pk::component_t componentId);
        void erase(pk::entity_t e, pk::component_t componentId);
        void entityDestroy(pk::entity_t e) override;
        void draw(const std::vector<std::pair<float, pk::entity_t>>& entities);
        void update(float dt);
        void clear() override;

    };


}

#endif //SYSTEM_H

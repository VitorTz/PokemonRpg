//
// Created by vitor on 9/14/24.
//

#ifndef SYSTEM_H
#define SYSTEM_H
#include "../pokemon.h"

namespace pk {

    class System {

    public:
        std::unordered_set<pk::entity_t> entities{};

    public:
        virtual ~System() = default;
        virtual void update(float dt) = 0;
        virtual void draw(sf::RenderWindow& window, pk::entity_t e) = 0;

    };

    class TransformSystem final : public pk::System {

    public:
        void update(float dt) override;
        void draw(sf::RenderWindow& window, pk::entity_t e) override;

    };

    class SpriteSystem final : public pk::System {

    public:
        void update(float dt) override;
        void draw(sf::RenderWindow& window, pk::entity_t e) override;

    };

    class CollisionBoxSystem final : public pk::System {

    public:
        void update(float dt) override;
        void draw(sf::RenderWindow& window, pk::entity_t e) override;

    };

    class WaterSystem final : public pk::System {

    public:
        void update(float dt) override;
        void draw(sf::RenderWindow& window, pk::entity_t e) override;

    };

    class CollisionBoxStaticSystem final : public pk::System {

    public:
        void update(float dt) override;
        void draw(sf::RenderWindow& window, pk::entity_t e) override;

    };

}

#endif //SYSTEM_H

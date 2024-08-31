#pragma once
#include <SFML/Graphics.hpp>
#include "../types.hpp"
#include <unordered_set>


namespace pk {

    class System {

        public:
            std::unordered_set<pk::entity_t> entities{};
        
        public:
            virtual ~System() = default;
            virtual void update(float dt) = 0;
            virtual void draw(sf::RenderWindow& window, pk::entity_t e) = 0;

    };


    class SpriteSystem : public pk::System {

        public:
            void update(float dt) override;
            void draw(sf::RenderWindow& window, pk::entity_t e) override;

    };

    class CollisionBodySystem : public pk::System {

        public:
            void update(float dt) override;
            void draw(sf::RenderWindow& window, pk::entity_t e) override;

    };

    
    class CollisionBodyStaticSystem : public pk::System {

        public:
            void update(float dt) override;
            void draw(sf::RenderWindow& window, pk::entity_t e) override;

    };
    
} // namespace pk

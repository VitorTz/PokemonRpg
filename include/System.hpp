#pragma once
#include <unordered_set>
#include "types.hpp"


namespace pk {


    class System {

        public:
            std::unordered_set<pk::entity_t> entities;

        public:
            virtual ~System() = default;            
            virtual void update(float dt) = 0;
            virtual void draw(pk::entity_t e) = 0;            

    };


    class SpriteSystem : public pk::System {

        public:
            void update(float dt) override;
            void draw(pk::entity_t e) override;            

    };


    class ObstacleSystem : public pk::System {

        public:
            void update(float dt) override;
            void draw(pk::entity_t e) override;            

    };
    
    
} // namespace pk

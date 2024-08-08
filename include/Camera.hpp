#pragma once
#include <raylib.h>
#include <vector>
#include <map>
#include <memory>
#include <array>
#include "SystemManager.hpp"
#include "ComponentManager.hpp"
#include "constants.hpp"
#include "types.hpp"


namespace pk {


    class Camera {

        private:
            Camera2D camera{.zoom = 1.0f};
            std::array<bool, pk::MAX_ENTITIES> isOnCamera{};
            std::map<pk::zindex_t, std::vector<std::pair<float, pk::entity_t>>> entitiesByIndex{};
        
        private:
            std::shared_ptr<pk::SystemManager> systemManager{};
            std::shared_ptr<pk::ComponentManager> componentManager{};
        
        public:
            Camera();
            void init(
                const std::shared_ptr<pk::SystemManager>& system,
                const std::shared_ptr<pk::ComponentManager>& component
            );
            void beginDrawing();
            void endDrawing();
            void move(float x, float y);
            void setCenter(Vector2 center);
            void setCenter(float x, float y);            
            Vector2 getCenter() const;
            void insert(pk::entity_t e, pk::zindex_t zindex);
            void erase(pk::entity_t e);
            void draw();
            void clear();
            std::size_t size() const;

    };

    inline pk::Camera gCamera{};
    
} // namespace pk

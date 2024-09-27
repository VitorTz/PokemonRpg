#pragma once
#include "raylib.h"
#include <map>
#include <vector>
#include <array>
#include "constants.hpp"
#include "types.hpp"



namespace pk {

    class Camera {

        private:
            Camera2D camera{};
            std::map<pk::zindex_t, std::vector<std::pair<float, pk::entity_t>>> cameraEntities{};
            std::array<bool, pk::MAX_ENTITIES> onCamera{};

        public:
            Camera();
            void addZoom(const float delta);
            void resetZoom();
            float getZoom() const;
            void beginDrawing();
            void endDrawing();
            void insert(pk::entity_t e);
            void erase(pk::entity_t e);
            void setTarget(Vector2 target);
            void setOffset(Vector2 offset);
            void sortEntitiesByCenterYpos();
            void clear();
            const std::map<pk::zindex_t, std::vector<std::pair<float, pk::entity_t>>>& getEntities() const;

    };

}
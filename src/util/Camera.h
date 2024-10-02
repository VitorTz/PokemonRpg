//
// Created by vitor on 9/30/24.
//

#ifndef CAMERA_H
#define CAMERA_H
#include "../pokemon.h"
#include "../ecs/System.h"

namespace pk {

    class Camera {

    private:
        Camera2D camera{};
        std::map<pk::zindex_t, std::vector<std::pair<float, pk::entity_t>>> zIndexToEntities{};
        std::array<bool, pk::MAX_ENTITIES> onCameraEntities{};
        std::size_t mSize{};
        const Vector2 mapSize;
        const pk::TiledMapId mapId;

    public:
        explicit Camera(pk::TiledMapId mapId);
        void move(float x, float y);

        void setTarget(float x, float y);
        void setTarget(const Vector2& v);
        void beginDrawing() const;
        void endDrawing() const;

        void insert(pk::entity_t e);
        void erase(pk::entity_t e);

        void draw(pk::SystemManager* system);
        void handleUserInput();
        void clear();
        std::size_t size() const;

        void setZoom(float z);
        void addZoom(float delta);
        float getZoom() const;

        void reset();

    };

}

#endif //CAMERA_H

//
// Created by vitor on 9/28/24.
//

#ifndef CAMERA_H
#define CAMERA_H
#include <raylib.h>
#include <map>
#include "../util/constants.h"
#include <vector>
#include "System.h"


namespace pk {

    class Camera {

    private:
        Camera2D camera{
            .offset = Vector2{pk::SCREEN_CENTERX, pk::SCREEN_CENTERY},
            .target = Vector2{pk::SCREEN_CENTERX, pk::SCREEN_CENTERY},
            .rotation = 0.0f,
            .zoom = 1.0f
        };
        std::map<pk::zindex_t, std::vector<std::pair<float, pk::entity_t>>> entities{};

    public:
        Camera();
        void addZoom(float z);
        void setZoom(float z);
        void resetZoom();
        void beginDrawing() const;
        void endDrawing() const;
        void insert(pk::entity_t e);
        void erase(pk::entity_t e);
        void draw(pk::SystemManager* systemManager);
        void setTarget(const Vector2& v);
        void setTarget(float x, float y);
        void move(float x, float y);
        void reset();
        void clear();

    };

    inline pk::Camera gCamera{};

}

#endif //CAMERA_H

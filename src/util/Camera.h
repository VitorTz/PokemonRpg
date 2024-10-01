//
// Created by vitor on 9/30/24.
//

#ifndef CAMERA_H
#define CAMERA_H
#include "../pokemon.h"


namespace pk {

    class Camera {

    private:
        Camera2D camera{
            .offset = Vector2{pk::SCREEN_CENTERX, pk::SCREEN_CENTERY},
            .target = Vector2{pk::SCREEN_CENTERX, pk::SCREEN_CENTERY},
            .rotation = 0.0f,
            .zoom = 2.0f
        };

    public:
        void reset();
        void addZoom(float delta);
        void setZoom(float z);
        void setTarget(float x, float y);
        void beginDrawing();
        void endDrawing();
        void handleMouseWheelInput();

    };

    inline pk::Camera gCamera{};

}

#endif //CAMERA_H

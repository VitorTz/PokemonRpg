//
// Created by vitor on 9/14/24.
//

#ifndef CAMERA_H
#define CAMERA_H
#include "pokemon.h"
#include "ecs/SysteManager.h"


namespace pk {

    class Camera {

    private:
        pk::CameraMap cameraMap{};
        std::array<bool, pk::MAX_ENTITIES> onCamera{};
        std::size_t mSize{};

    public:
        Camera();
        void insert(pk::entity_t e);
        void erase(pk::entity_t e);
        void draw(sf::RenderWindow& window, pk::SystemManager* system);
        void clear();
        std::size_t size() const;

    };

    inline pk::Camera gCamera{};

}


#endif //CAMERA_H

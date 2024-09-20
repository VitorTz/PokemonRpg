//
// Created by vitor on 9/14/24.
//

#ifndef CAMERA_H
#define CAMERA_H
#include "../pokemon.h"
#include "../ecs/SystemManager.h"


namespace pk {

    class Camera {

    private:
        pk::CameraMap cameraMap{};
        std::array<bool, pk::MAX_ENTITIES> onCamera{};
        std::size_t mSize{};
        sf::View view{};
        sf::FloatRect cameraRect{};
        float zoom{1.0f};

    public:
        Camera();
        void insert(pk::entity_t e);
        void erase(pk::entity_t e);
        void setView(sf::RenderWindow& window) const;
        void draw(sf::RenderWindow& window, pk::SystemManager* system);
        void clear();
        void setCenter(const sf::Vector2f& center);
        void setCenter(float x, float y);
        void addZoom(float z);
        void setZoom(float z);
        float getZoom() const;
        const sf::FloatRect& getCameraRect() const;
        std::size_t size() const;

    };

    inline pk::Camera gCamera{};

}


#endif //CAMERA_H

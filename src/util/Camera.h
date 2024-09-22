//
// Created by vitor on 9/21/24.
//
#ifndef CAMERA_H
#define CAMERA_H
#include "../pokemon.h"
#include "../ecs/System.h"


namespace pk {

    class Camera {

    private:
        sf::View view{};
        std::unordered_map<pk::zindex_t, std::vector<std::pair<float, pk::entity_t>>> camera{};
        std::array<bool, pk::MAX_ENTITIES> isOnCamera{};
        std::size_t mSize{};

    public:
        Camera();
        void insert(pk::entity_t e);
        void erase(pk::entity_t e);
        void clear();
        void draw(sf::RenderWindow& window, pk::SystemManager* system);
        void setCenter(const sf::Vector2f& center);
        void setCenter(float x, float y);
        std::size_t size() const;

    };

    inline pk::Camera gCamera{};

}

#endif //CAMERA_H

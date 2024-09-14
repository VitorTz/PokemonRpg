//
// Created by vitor on 9/14/24.
//

#ifndef COMPONENTS_H
#define COMPONENTS_H
#include "../pokemon.h"
#include "../TexturePool.h"


namespace pk {

    constexpr std::size_t NUM_COMPONENTS{5};

    typedef struct transform {
        sf::Vector2f pos{};
        sf::Vector2f size{};
        sf::Vector2f scale{1.0f, 1.0f};
        pk::zindex_t zindex{};
        float rotation{};
        transform() = default;
        explicit transform(const pk::zindex_t z) : zindex(z) { }
    } transform_t;

    typedef struct sprite {
        sf::Sprite sfSprite{};
        sf::Vector2f size{};
        sprite() = default;
        explicit sprite(
            const char* fileName
        ) : sfSprite(pk::gTexturePool.get(fileName)),
            size(static_cast<sf::Vector2f>(sfSprite.getTexture()->getSize())) { }
    } sprite_t;

    typedef struct collision_box_static {
        sf::FloatRect rect{};
    } collision_box_static_t;

    typedef struct collision_box {
        sf::FloatRect rect{};
    } collision_box_t;

    typedef struct water {
        bool isCoast{};
    } water_t;

}

#endif //COMPONENTS_H

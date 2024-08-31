#pragma once
#include "../types.hpp"
#include "../TexturePool.hpp"


namespace pk {

    constexpr std::size_t NUM_COMPONENTS{4};

    typedef struct transform {
        sf::Vector2f pos{};
        sf::Vector2f size{};
        sf::Vector2f scale{1.0f, 1.0f};
        float rotation{};
        pk::zindex_t zindex{};
        transform() = default;
        transform(pk::zindex_t zindex) : zindex(zindex) { }
    } transform_t;

    typedef struct sprite {
        sf::Sprite sfSprite;
        sprite() = default;
        sprite(const char* filePath) : sfSprite(pk::gTexturePool.get(filePath)) { }
    } sprite_t;

    typedef struct collision_body {
        sf::FloatRect rect{};
        sf::Vector2f offset{};
    } collision_body_t;

    typedef struct collision_body_static {
        sf::FloatRect rect{};
    } collision_body_static_t;
    
} // namespace pk

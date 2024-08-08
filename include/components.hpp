#pragma once
#include "TexturePool.hpp"
#include "constants.hpp"
#include "types.hpp"


namespace pk {

    constexpr std::size_t NUM_COMPONENTS = 3;

    typedef struct transform {
        Vector2 pos{};
        Vector2 size{};
        pk::zindex_t zindex{};
    } transform_t;

    typedef struct sprite {
        Texture2D texture{};
        sprite() = default;
        sprite(
            const char* fileName
        ) : texture(pk::gTexturePool.load(fileName)) { } 
    } sprite_t;
    
    typedef struct obstacle {
        Rectangle rect{};
    } obstacle_t;    
    
} // namespace pk

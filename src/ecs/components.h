//
// Created by vitor on 9/30/24.
//

#ifndef COMPONENTS_H
#define COMPONENTS_H
#include "../util/TexturePool.h"
#include "../pokemon.h"
#include "../util/util.h"


namespace pk {

    namespace id { // Components IDS

        constexpr pk::component_t transform = 0;
        constexpr pk::component_t sprite = 1;
        constexpr pk::component_t sprite_animation = 2;
        constexpr pk::component_t player = 3;

    }

    constexpr std::size_t NUM_COMPONENTS{3};

    typedef struct transform {
        Vector2 pos{};
        Vector2 size{};
        pk::zindex_t zindex{};
        transform() = default;
        explicit transform(const pk::zindex_t zindex) : zindex(zindex) { }
    } transform_t;

    typedef struct sprite {
        Texture2D texture{};
        sprite() = default;
        explicit sprite(const char* fileName) : texture(pk::gTexturePool.load(fileName)) { }
    } sprite_t;

    typedef struct sprite_animation {
        Texture2D texture{};
        Rectangle rect{};
        std::uint8_t frame{};
        std::uint8_t maxFrame{};
        std::uint8_t counter{};
        std::uint8_t speed{};
        std::uint8_t cols{};
        sprite_animation() = default;
        sprite_animation(
            const char* fileName,
            const std::uint8_t rows,
            const std::uint8_t cols,
            const std::uint8_t speed
        ) : texture(pk::gTexturePool.load(fileName)), maxFrame(rows * cols), speed(speed), cols(cols) {
            this->rect.width = texture.width / cols;
            this->rect.height = texture.height / rows;
        }
        explicit sprite_animation(
            const pk::sprite_animation_source_t& animation
        ) : sprite_animation(animation.fileName, animation.rows, animation.cols, animation.speed) { }
    } sprite_animation_t;

    typedef struct water {
        pk::WaterType type{};
    } water_t;


}

#endif //COMPONENTS_H

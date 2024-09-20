//
// Created by vitor on 9/14/24.
//

#ifndef COMPONENTS_H
#define COMPONENTS_H
#include "../pokemon.h"
#include "../util/TexturePool.h"


namespace pk {

    constexpr std::size_t NUM_COMPONENTS{8};

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
            size(static_cast<sf::Vector2f>(sfSprite.getTexture()->getSize())) {
            sfSprite.setOrigin(size.x / 2.0f, size.y / 2.0f);
        }
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

    typedef struct bezier_curve {
        std::vector<sf::Vector2f> points{};
        float currentTime{};
        float maxTime{};
        bezier_curve() = default;
        explicit bezier_curve(const float maxTime) : maxTime(maxTime) { }
    } bezier_curve_t;

    typedef struct sprite_animation {
        sf::Sprite sprite{};
        sf::IntRect rect{};
        pk::FrameCounter counter;
        std::uint32_t cols{};
        sprite_animation() = default;
        explicit sprite_animation(
            const pk::asset_t& asset,
            const pk::animation_speed_t animationSpeed
        ) : sprite(pk::gTexturePool.get(asset.path.c_str())),
            counter(animationSpeed, asset.rows * asset.cols),
            cols(asset.cols) {
                this->sprite.setOrigin(static_cast<float>(asset.spriteWidth) / 2.0f, static_cast<float>(asset.spriteHeight) / 2.0f);
                this->rect.width = static_cast<int>(asset.spriteWidth);
                this->rect.height = static_cast<int>(asset.spriteHeight);
            }
    } sprite_animation_t;

    typedef struct boat {
        pk::State state{pk::State::Paused};
    } boat_t;

}

#endif //COMPONENTS_H

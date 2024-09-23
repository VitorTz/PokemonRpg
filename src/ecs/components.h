//
// Created by vitor on 9/21/24.
//

#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <SFML/Graphics.hpp>
#include "../util/AssetPool.h"
#include "../util/FrameCounter.h"
#include "../util/types.h"


namespace pk {

    constexpr std::size_t NUM_COMPONENTS{6};

    typedef struct transform {
        sf::Vector2f pos;
        sf::Vector2f size;
        sf::Vector2f scale{1.0f, 1.0f};
        char directionStatus[2]{'i', 'd'};
        sf::Vector2f direction{};
        float speed{};
        float rotation{0.0f};
        pk::zindex_t zindex{};
        transform() = default;
        explicit transform(const pk::zindex_t zindex) : zindex(zindex) { }
        explicit transform(const sf::Vector2f& pos, const pk::zindex_t zindex) : pos(pos), zindex(zindex) { }
    } transform_t;

    typedef struct movement {

    } movement_t;

    typedef struct sprite {
        sf::Sprite spr{};
        sprite() = default;
        explicit  sprite(const char* filePath) : spr(pk::gTexturePool.get(filePath)) {
            const sf::Vector2u spriteSize = spr.getTexture()->getSize();
            spr.setOrigin(static_cast<float>(spriteSize.x) / 2.0f, static_cast<float>(spriteSize.y) / 2.0f);
        }
    } sprite_t;

    typedef struct collision {
        sf::FloatRect rect{};
    } collision_t;

    typedef struct sprite_animation {
        sf::Sprite sprite{};
        sf::IntRect rect{};
        pk::FrameCounter counter{};
        std::uint8_t cols{};
        sprite_animation() = default;
        explicit sprite_animation(
            const pk::sprite_animation_source_t& source
        ) : sprite(pk::gTexturePool.get(source.filePath)),
            rect(0, 0, source.spriteWidth, source.spriteHeight),
            counter(source.speed, source.rows * source.cols),
            cols(source.cols) {
            sprite.setOrigin(static_cast<float>(source.spriteWidth) / 2.0f,  static_cast<float>(source.spriteHeight) / 2.0f);
        }
    } sprite_animation_t;

    typedef struct player {
        pk::entity_t playerEntity{};
        pk::entity_t shadowEntity{};
        sf::FloatRect collisionRect{};
        sf::FloatRect actionRect{};
        char direction[2]{'i', 'd'};
        char action{'x'};
    } player_t;

    inline pk::player_t gPlayer{};

}

#endif //COMPONENTS_H

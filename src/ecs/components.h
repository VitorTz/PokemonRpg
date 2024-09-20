//
// Created by vitor on 9/14/24.
//

#ifndef COMPONENTS_H
#define COMPONENTS_H
#include "../pokemon.h"
#include "../util/TexturePool.h"


namespace pk {

    constexpr std::size_t NUM_COMPONENTS{9};
    constexpr std::size_t NUM_VALID_COMPONENTS{8};

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
            const char* filePath,
            const float spriteWidth,
            const float spriteHeight,
            const std::uint32_t rows,
            const std::uint32_t cols,
            const pk::animation_speed_t speed
        ) : sprite(pk::gTexturePool.get(filePath)),
            counter(speed, rows * cols),
            cols(cols) {
                this->sprite.setOrigin(spriteWidth / 2.0f, spriteHeight / 2.0f);
                this->rect.width = spriteWidth;
                this->rect.height = spriteHeight;
            }
    } sprite_animation_t;

    typedef struct player {
        pk::entity_t playerEntity{};
        pk::entity_t shadowEntity{};
        sf::FloatRect collideRect{};
        sf::FloatRect actionRect{};
        char direction{'d'}; // d: down, u: up, r: right, l: left
        char action{'i'}; // i: idle, a: attack
    } player_t;

    typedef struct boat {
        pk::State state{pk::State::Paused};
    } boat_t;

}

#endif //COMPONENTS_H

//
// Created by vitor on 9/28/24.
//

#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <raylib.h>
#include <vector>
#include "../util/TexturePool.h"
#include "../util/types.h"


namespace pk {

    constexpr std::size_t NUM_COMPONENTS{6};

    typedef struct transform {
        Rectangle rect{};
        pk::zindex_t zindex{};
        float rotation{};
        transform() = default;
        explicit transform(const pk::zindex_t zindex) : zindex(zindex) { }
    } transform_t;

    typedef struct sprite {
        Texture2D texture{};
        sprite() = default;
        explicit sprite(const char* fileName) : texture(pk::gTexturePool.get(fileName)) { }
    } sprite_t;

    typedef struct collision {
        Rectangle rect{};
    } collision_t;

    typedef struct movement {
        char direction[2]{'i', 'd'};
        int currentTile{};
        int targetTile{};
        std::vector<int> path{};
    } movement_t;

    typedef struct sprite_animation {
        Texture2D texture{};
        Rectangle rect{};
    } sprite_animation_t;

    typedef struct player {
        pk::entity_t playerEntity{};
        pk::entity_t shadowEntity{};
        Rectangle collisionRect{};
        Rectangle actionRect{};
        char action{'x'};
    } player_t;

}

#endif //COMPONENTS_H

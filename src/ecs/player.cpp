//
// Created by vitor on 9/20/24.
//
#include "player.h"
#include "ECS.h"
#include "../util/util.h"


void pk::playerCreate() {
    // player
    pk::gPlayer.playerEntity = pk::gEcs.entityCreate(pk::PLAYER_ZINDEX, true);
    pk::addSpriteAnimation(pk::gPlayer.playerEntity, CHARACTERS_PATH "player.png", pk::PLAYER_WIDTH, pk::PLAYER_HEIGHT, 4, 4, pk::PLAYER_ANIMATION_SPEED);
    // player shadow
    pk::gPlayer.shadowEntity = pk::gEcs.entityCreate(pk::PLAYER_SHADOW_ZINDEX, true);
    pk::addSpriteToEntity(pk::gPlayer.shadowEntity, GRAPHICS_PATH "other/shadow.png");
    // Collide Rect
    pk::gPlayer.collideRect = {0.0f, 0.0f, pk::PLAYER_COLLISION_WIDTH, pk::PLAYER_COLLISION_HEIGHT};
}


sf::Vector2f pk::playerCenter() {
    return pk::gEcs.getTransform(pk::gPlayer.playerEntity).pos;
}



//
// Created by vitor on 9/20/24.
//
#include "ECS.h"
#include "System.h"
#include "player.h"
#include "../util/util.h"


void pk::PlayerSystem::update(const float dt) {
    pk::sprite_animation_t& spriteAnimation = pk::gEcs.getComponent<pk::sprite_animation_t>(pk::gPlayer.playerEntity);
    pk::transform_t& playerTransform = pk::gEcs.getTransform(pk::gPlayer.playerEntity);
    pk::transform_t& shadowTransform = pk::gEcs.getTransform(pk::gPlayer.shadowEntity);

    // Movement
    const pk::movement_direction_t direction = pk::getMoveDirection();
    const char lastDirectionChar = pk::gPlayer.direction;
    pk::gPlayer.direction = direction.action != 'i' ? direction.directionChar : lastDirectionChar;
    pk::gPlayer.action = direction.action;
    playerTransform.pos.x += direction.direction.x * pk::PLAYER_SPEED * dt;
    playerTransform.pos.y += direction.direction.y * pk::PLAYER_SPEED * dt;

    // Collision
    pk::gPlayer.collideRect.left = playerTransform.pos.x - pk::PLAYER_HALF_COLLISION_WIDTH;
    pk::gPlayer.collideRect.top = playerTransform.pos.y;

    // Action Box
    pk::gPlayer.actionRect.top = playerTransform.pos.y;
    switch (pk::gPlayer.direction) {
        case 'u':
            pk::gPlayer.actionRect.left = playerTransform.pos.x - pk::PLAYER_ACTION_BOX_SIZE_Y[0] / 2.0f;
            pk::gPlayer.actionRect.top -= pk::PLAYER_ACTION_BOX_Y_OFFSET + 30.0f;
            pk::gPlayer.actionRect.width = pk::PLAYER_ACTION_BOX_SIZE_Y[0];
            pk::gPlayer.actionRect.height = pk::PLAYER_ACTION_BOX_SIZE_Y[1] + 30.0f;
            break;
        case 'd':
            pk::gPlayer.actionRect.left = playerTransform.pos.x - pk::PLAYER_ACTION_BOX_SIZE_Y[0] / 2.0f;
            pk::gPlayer.actionRect.top += pk::PLAYER_ACTION_BOX_Y_OFFSET;
            pk::gPlayer.actionRect.width = pk::PLAYER_ACTION_BOX_SIZE_Y[0];
            pk::gPlayer.actionRect.height = pk::PLAYER_ACTION_BOX_SIZE_Y[1];
            break;
        case 'l':
            pk::gPlayer.actionRect.left = playerTransform.pos.x - pk::PLAYER_ACTION_BOX_SIZE_X[0] / 2.0f - pk::PLAYER_ACTION_BOX_X_OFFSET;
            pk::gPlayer.actionRect.top = playerTransform.pos.y - pk::PLAYER_ACTION_BOX_SIZE_X[1] / 2.0f;
            pk::gPlayer.actionRect.width = pk::PLAYER_ACTION_BOX_SIZE_X[0];
            pk::gPlayer.actionRect.height = pk::PLAYER_ACTION_BOX_SIZE_X[1];
            break;
        case 'r':
            pk::gPlayer.actionRect.left = playerTransform.pos.x - pk::PLAYER_ACTION_BOX_SIZE_X[0] / 2.0f + pk::PLAYER_ACTION_BOX_X_OFFSET;;
            pk::gPlayer.actionRect.top = playerTransform.pos.y - pk::PLAYER_ACTION_BOX_SIZE_X[1] / 2.0f;
            pk::gPlayer.actionRect.width = pk::PLAYER_ACTION_BOX_SIZE_X[0];
            pk::gPlayer.actionRect.height = pk::PLAYER_ACTION_BOX_SIZE_X[1];
            break;
        default:
            break;
    }

    // Sprite Animation
    spriteAnimation.rect.left = pk::gPlayer.action == 'i' ? 0 : spriteAnimation.rect.left;
    switch (pk::gPlayer.direction) {
        case 'u':
            spriteAnimation.rect.top = 192;
            break;
        case 'd':
            spriteAnimation.rect.top = 0;
            break;
        case 'l':
            spriteAnimation.rect.top = 64;
            break;
        case 'r':
            spriteAnimation.rect.top = 128;
            break;
        default:
            break;
    }

    // Shadow
    shadowTransform.pos.x = playerTransform.pos.x;
    shadowTransform.pos.y = playerTransform.pos.y + pk::PLAYER_HALF_HEIGHT;
}


void pk::PlayerSystem::draw([[maybe_unused]] sf::RenderWindow &window, [[maybe_unused]] pk::entity_t e) {

}


//
// Created by vitor on 10/1/24.
//
#include "ECS.h"
#include "player.h"
#include "System.h"



pk::PlayerSystem::PlayerSystem(const pk::TiledMapId mapId) : pk::System(mapId) {

}


void pk::PlayerSystem::update(const float dt) {
    pk::ECS* ecs = pk::ECS::getInstance(this->mapId);
    pk::player_info_t* playerInfo = ecs->getPlayerInfo();
    pk::Camera* camera = ecs->getCamera();

    // Components
        pk::transform_t& transform = ecs->getTransform(playerInfo->playerEntity);
        pk::sprite_animation_t& spriteAnimation = ecs->getComponent<pk::sprite_animation_t, id::sprite_animation>(playerInfo->playerEntity);

    // Movement
        Vector2 direction{};
        playerInfo->directionState[0] = 'i';

        if (IsKeyDown(KEY_W)) {
            direction.y = -1.0f;
            playerInfo->directionState[0] = 'm';
            playerInfo->directionState[1] = 'u';
        } else if (IsKeyDown(KEY_S)) {
            direction.y = 1.0f;
            playerInfo->directionState[0] = 'm';
            playerInfo->directionState[1] = 'd';
        }
        if (IsKeyDown(KEY_A)) {
            direction.x = -1.0f;
            playerInfo->directionState[0] = 'm';
            playerInfo->directionState[1] = 'l';
        } else if (IsKeyDown(KEY_D)) {
            direction.x = 1.0f;
            playerInfo->directionState[0] = 'm';
            playerInfo->directionState[1] = 'r';
        }

        direction = Vector2Normalize(direction);
        const float deltaX = direction.x * dt * pk::PLAYER_SPEED;
        const float deltaY = direction.y * dt * pk::PLAYER_SPEED;

        // Horizontal movement
        transform.pos.x += deltaX;
        playerInfo->collisionRect.x += deltaX;
        if (ecs->checkCollision(playerInfo->collisionRect)) {
            transform.pos.x -= deltaX;
            playerInfo->collisionRect.x -= deltaX;
        }

        // Vertical movement
        transform.pos.y += deltaY;
        playerInfo->collisionRect.y += deltaY;
        if (ecs->checkCollision(playerInfo->collisionRect)) {
            transform.pos.y -= deltaY;
            playerInfo->collisionRect.y -= deltaY;
        }

    camera->setTarget(transform.pos.x + transform.size.x / 2.0f, transform.pos.y + transform.size.y / 2.0f);

    if (playerInfo->directionState[0] == 'i') {
        spriteAnimation.rect.x = 0.0f;
    }

    switch (playerInfo->directionState[1]) {
        case 'd':
            spriteAnimation.rect.y = 0.0f;
            break;
        case 'l':
            spriteAnimation.rect.y = pk::PLAYER_SIZE;
            break;
        case 'r':
            spriteAnimation.rect.y = pk::PLAYER_SIZE * 2;
            break;
        case 'u':
            spriteAnimation.rect.y = pk::PLAYER_SIZE * 3;
            break;
        default:
            break;
    }

}


void pk::PlayerSystem::draw(pk::entity_t e) {

}


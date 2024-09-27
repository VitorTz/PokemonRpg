#pragma once
#include "raylib.h"
#include "types.hpp"


#define ASSETS_PATH "./src/resources/"

namespace pk {

    // Window
    constexpr float SCREEN_W{1280.0f};
    constexpr float SCREEN_H{720.0f};
    constexpr float SCREEN_CENTERX{SCREEN_W / 2.0f};
    constexpr float SCREEN_CENTERY{SCREEN_H / 2.0f};
    constexpr float SCREEN_SIZE[2]{SCREEN_W, SCREEN_H};
    constexpr float SCREEN_CENTER[2]{SCREEN_CENTERX, SCREEN_CENTERY};
    constexpr char WINDOW_TITLE[]{"Pokemon"};

    // ECS
    constexpr pk::entity_t MAX_ENTITIES{4086};

    // Scenes
    constexpr pk::SceneId MAIN_SCENE{pk::SceneId::TestScene1Id};

    // Camera
    constexpr float CAMERA_MIN_ZOOM{0.25};
    constexpr float CAMERA_MAX_ZOOM{2};
    constexpr float CAMERA_MIN_ZINDEX{0};
    constexpr float CAMERA_MAX_ZINDEX{10};

    // Animation
    constexpr int ANIMATION_SPEED_SLOW{12};
    constexpr int ANIMATION_SPEED_NORMAL{8};
    constexpr int ANIMATION_SPEED_FAST{4};


    // Player
    constexpr float PLAYER_WIDTH{32.0f};
    constexpr Rectangle PLAYER_COLLISION_RECT{0.0f, 0.0f, pk::PLAYER_WIDTH * 0.80f, pk::PLAYER_WIDTH * 0.60f};
    constexpr Rectangle PLAYER_ACTION_RECT{0.0f, 0.0f, 40.0f, 40.0f};
    constexpr pk::sprite_animation_info_t PLAYER_SPRITE_ANIMATION{
        ASSETS_PATH "graphics/characters/player.png",
        4,
        4,
        pk::ANIMATION_SPEED_NORMAL,
        16
    };

}
//
// Created by vitor on 9/30/24.
//

#ifndef POKEMON_H
#define POKEMON_H
#include <raylib.h>
#include <raymath.h>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <random>
#include <cmath>
#include <vector>
#include <array>
#include <thread>
#include <mutex>
#include <filesystem>
#include <fstream>
#include <memory>
#include <iostream>
#include <cstdio>
#include <cassert>
#include <queue>
#include <algorithm>
#include "util/WaterType.h"
#include "util/types.h"
#include "util/SceneId.h"
#include "util/TiledMapId.h"


#define ASSETS_PATH "./assets/"
#define GRAPHICS_PATH ASSETS_PATH "graphics/"
#define CHARACTERS_PATH GRAPHICS_PATH "characters/"


namespace pk {

    // Window
    constexpr float SCREEN_W{1280.0f};
    constexpr float SCREEN_H{720.0f};
    constexpr float SCREEN_CENTERX{SCREEN_W / 2.0f};
    constexpr float SCREEN_CENTERY{SCREEN_H / 2.0f};
    constexpr char WINDOW_TITLE[]{"Pokemon Rpg"};
    constexpr int TARGET_FPS{60};
    constexpr float SCREEN_SIZE[2]{SCREEN_W, SCREEN_H};
    constexpr float SCREEN_CENTER[2]{SCREEN_CENTERX, SCREEN_CENTERY};
    constexpr bool DEBUG_MODE{true};

    constexpr pk::SceneId MAIN_SCENE{pk::TestScene1Id};
    constexpr pk::entity_t MAX_ENTITIES{4096};

    // Camera
    constexpr float CAMERA_MIN_ZOOM{0.5f};
    constexpr float CAMERA_MAX_ZOOM{2.0f};

    constexpr pk::zindex_t ZINDEX_MAX{4};
    constexpr pk::zindex_t ZINDEX_SKY{4};
    constexpr pk::zindex_t ZINDEX_WORLD{3};
    constexpr pk::zindex_t ZINDEX_SHADOW{2};
    constexpr pk::zindex_t ZINDEX_WATER{1};
    constexpr pk::zindex_t ZINDEX_TERRAIN{0};
    constexpr pk::zindex_t ZINDEX_MIN{0};

    // Maps
    constexpr int TILE_SIZE{64};

    constexpr std::array<pk::tiled_map_t, pk::NumTiledMaps> TILED_MAP = {
        pk::tiled_map_t{
            "world",
            86,
            86,
            Vector2{86 * pk::TILE_SIZE, 86 * pk::TILE_SIZE}
        }
    };

    // Animation
    constexpr std::uint8_t ANIMATION_SPEED_SLOW{12};
    constexpr std::uint8_t ANIMATION_SPEED_NORMAL{8};
    constexpr std::uint8_t ANIMATION_SPEED_FAST{4};

    // Player
    constexpr float PLAYER_SIZE{128.0f};
    constexpr float PLAYER_SPEED{150.0f};
    constexpr Rectangle PLAYER_COLLISION_RECT{0.0f, 0.0f, pk::TILE_SIZE * 0.6, pk::TILE_SIZE * 0.6};
    constexpr std::array<Vector2, pk::NumTiledMaps> PLAYER_START_POS = {
        Vector2{400.0f, 400.0f}
    };
    constexpr pk::sprite_animation_source_t PLAYER_SPRITE_ANIMATION = {
        CHARACTERS_PATH "player.png",
        4, 4,
        pk::ANIMATION_SPEED_NORMAL
    };


}


#endif //POKEMON_H

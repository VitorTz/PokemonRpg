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
#include "util/types.h"
#include "util/SceneId.h"
#include "util/TiledMapId.h"


#define ASSETS_PATH "./assets/"
#define GRAPHICS_PATH ASSETS_PATH "graphics/"
#define CHARACTERS_PATH GRAPHICS_PATH "characters/"
#define TILED_MAP_PATH ASSETS_PATH "tiled-map/"


namespace pk {

    constexpr float SCREEN_W{1280.0f};
    constexpr float SCREEN_H{720.0f};
    constexpr float SCREEN_CENTERX{SCREEN_W / 2.0f};
    constexpr float SCREEN_CENTERY{SCREEN_H / 2.0f};
    constexpr char WINDOW_TITLE[]{"Pokemon Rpg"};
    constexpr float SCREEN_SIZE[2]{SCREEN_W, SCREEN_H};
    constexpr float SCREEN_CENTER[2]{SCREEN_CENTERX, SCREEN_CENTERY};

    constexpr pk::entity_t MAX_ENTITIES{4096};

    constexpr pk::SceneId MAIN_SCENE{pk::TestScene1Id};

    // Camera
    constexpr float CAMERA_MIN_ZOOM{0.25f};
    constexpr float CAMERA_MAX_ZOOM{2.5f};
    constexpr pk::zindex_t CAMERA_MIN_ZINDEX{0};
    constexpr pk::zindex_t CAMERA_MAX_ZINDEX{10};

    constexpr std::array<const char*, pk::NumTiledMaps> MAP_PATH = {
        TILED_MAP_PATH "world/"
    };

    constexpr std::uint8_t ANIMATION_SPEED_SLOW{12};
    constexpr std::uint8_t ANIMATION_SPEED_NORMAL{8};
    constexpr std::uint8_t ANIMATION_SPEED_FAST{4};

    constexpr float PLAYER_SIZE{32.0f};
    constexpr pk::zindex_t PLAYER_ZINDEX{2};
    constexpr pk::zindex_t PLAYER_SHADOW_ZINDEX{1};
    constexpr pk::sprite_animation_source_t PLAYER_SPRITE_ANIMATION = {
        CHARACTERS_PATH "player.png",
        4,
        4,
        pk::ANIMATION_SPEED_NORMAL
    };


}


#endif //POKEMON_H

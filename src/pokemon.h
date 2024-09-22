//
// Created by vitor on 9/21/24.
//

#ifndef POKEMON_H
#define POKEMON_H
#include <array>
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <SFML/Graphics.hpp>
#include <thread>
#include <cassert>
#include "util/FontID.h"
#include "util/util.h"
#include "util/types.h"
#include "util/TypeID.h"


#define AUDIO_PATH ASSETS_PATH "audio/"
#define MAPS_PATH ASSETS_PATH "data/maps/"
#define GRAPHICS_PATH ASSETS_PATH "graphics/"
#define CHARACTERS_PATH ASSETS_PATH "graphics/characters/"


namespace pk {

    // Window
    constexpr float SCREEN_W{1280.0f};
    constexpr float SCREEN_H{720.0f};
    constexpr float SCREEN_SIZE[2]{SCREEN_W, SCREEN_H};
    constexpr float SCREEN_CENTERX{SCREEN_W / 2.0f};
    constexpr float SCREEN_CENTERY{SCREEN_H / 2.0f};
    constexpr float SCREEN_CENTER[2]{SCREEN_CENTERX, SCREEN_CENTERY};
    constexpr char WINDOW_TITLE[]{"Pokemon"};

    // Game
    constexpr float TILE_SIZE{16.0f};
    constexpr pk::entity_t MAX_ENTITIES{4096};
    constexpr float WORLD_WIDTH{4096};
    constexpr float WORLD_HEIGHT{4096};
    constexpr float WORLD_CENTERX{pk::WORLD_WIDTH / 2.0f};
    constexpr float WORLD_CENTERY{pk::WORLD_HEIGHT / 2.0f};

    // Animation Speed
    constexpr int ANIMATION_SPEED_SLOW{60 / 4};
    constexpr int ANIMATION_SPEED_NORMAL{60 / 8};
    constexpr int ANIMATION_SPEED_FAST{60 / 12};

    constexpr pk::zindex_t CAMERA_MIN_ZINDEX{0};
    constexpr pk::zindex_t CAMERA_MAX_ZINDEX{10};

    // Player
    constexpr float PLAYER_SIZE{64.0f};

    // Sprite Animation
    constexpr pk::sprite_animation_source_t PLAYER_SPRITE_ANIMATION{
        ASSETS_PATH "graphics/characters/player.png",
        static_cast<int>(PLAYER_SIZE),
        static_cast<int>(PLAYER_SIZE),
        4,
        4,
        pk::ANIMATION_SPEED_NORMAL
    };

}


#endif //POKEMON_H

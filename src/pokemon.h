//
// Created by vitor on 9/14/24.
//

#ifndef POKEMON_H
#define POKEMON_H

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <memory>
#include <array>
#include <queue>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <cstdint>
#include <filesystem>
#include <cmath>
#include <fstream>
#include <typeinfo>
#include <cassert>
#include <thread>
#include <random>
#include "util/FrameCounter.h"

#define GRAPHICS_PATH ASSETS_PATH "graphics/"
#define CHARACTERS_PATH ASSETS_PATH "graphics/characters/"

namespace pk {

    // ECS
        typedef std::uint32_t entity_t;
        typedef std::uint8_t component_t;
        typedef std::uint8_t zindex_t;
        typedef std::uint32_t animation_speed_t;
        constexpr pk::entity_t MAX_ENTITIES{4096};

    // Game
        typedef std::vector<std::pair<float, pk::entity_t>> OrderedEntityVector;
        typedef std::map<pk::zindex_t, pk::OrderedEntityVector> CameraMap;

    // Window
        constexpr unsigned int SCREEN_W{1280};
        constexpr unsigned int SCREEN_H{720};
        constexpr char WINDOW_TITLE[]{"Pokemon Rpg"};
        constexpr float SCREEN_WF{static_cast<float>(SCREEN_W)};
        constexpr float SCREEN_HF{static_cast<float>(SCREEN_H)};
        constexpr float SCREEN_CENTERX{SCREEN_WF / 2.0f};
        constexpr float SCREEN_CENTERY{SCREEN_HF / 2.0f};
        const static sf::Vector2f SCREEN_SIZE(pk::SCREEN_WF, pk::SCREEN_HF);
        const static sf::Vector2f SCREEN_CENTER(pk::SCREEN_CENTERX, pk::SCREEN_CENTERY);
        const static sf::FloatRect SCREEN_RECT(0.0f, 0.0f, SCREEN_WF, SCREEN_HF);

    // World Map
        constexpr float WORLD_WIDTH{4096.0f};
        constexpr float WORLD_HEIGHT{4096.0f};
        constexpr float WORLD_CENTERX{pk::WORLD_WIDTH / 2.0f};
        constexpr float WORLD_CENTERY{pk::WORLD_HEIGHT / 2.0f};
        const static sf::Vector2f WORLD_SIZE(pk::WORLD_WIDTH, pk::WORLD_HEIGHT);
        constexpr float TILE_SIZE{16.0f};

    // Camera
        constexpr pk::zindex_t CAMERA_MIN_ZINDEX{0};
        constexpr pk::zindex_t CAMERA_MAX_ZINDEX{10};
        constexpr float CAMERA_ZOOM_SPEED{0.25f};
        constexpr float CAMERA_MIN_ZOOM{0.25f};
        constexpr float CAMERA_MAX_ZOOM{4.0f};


    // Animation
        constexpr pk::animation_speed_t ANIMATION_SPEED_SLOW{60 / 4};
        constexpr pk::animation_speed_t ANIMATION_SPEED_NORMAL{60 / 8};
        constexpr pk::animation_speed_t ANIMATION_SPEED_FAST{60 / 12};

    // Scene
        enum SceneId {
            TitleScreenId,
            LevelSceneId,
            LoadingScreenId,
            TestScene1Id
        };
        constexpr pk::SceneId MAIN_SCENE{pk::TestScene1Id};

    // Player
        constexpr std::uint32_t PLAYER_WIDTH{64};
        constexpr std::uint32_t PLAYER_HEIGHT{64};
        constexpr float PLAYER_SPEED{150.0f};
        constexpr pk::animation_speed_t PLAYER_ANIMATION_SPEED{pk::ANIMATION_SPEED_NORMAL};

    // Water
        const static sf::Vector2f WATER_POS_COAST{0.0f, 3456.0f};
        const static sf::Vector2f WATER_POS{0.0f, 3472.0f};
        constexpr std::size_t WATER_SPRITES_NUM{2};
        constexpr pk::animation_speed_t WATER_ANIMATION_SPEED{pk::ANIMATION_SPEED_SLOW};
        constexpr std::array<const char*, 4> WATER_SPRITES = {
            ASSETS_PATH "graphics/water/water1.png",
            ASSETS_PATH "graphics/water/water2.png",
            ASSETS_PATH "graphics/water/water3.png",
            ASSETS_PATH "graphics/water/water4.png"
        };

    // Aux
        enum State {
            Active,
            Paused
        };

    // Assets
        enum AssetId {
            PlayerAssetId
        };
        typedef struct asset {
            pk::AssetId id{};
            std::string path{};
            std::uint8_t rows{};
            std::uint8_t cols{};
            std::uint32_t spriteWidth{};
            std::uint32_t spriteHeight{};
        } asset_t;

        const static std::unordered_map<pk::AssetId, asset_t> ASSETS_MAP = {
            {
                PlayerAssetId,
                {
                    PlayerAssetId,
                    CHARACTERS_PATH "player.png",
                    4,
                    4,
                    pk::PLAYER_WIDTH,
                    pk::PLAYER_HEIGHT
                }
            }
        };

}

#endif //POKEMON_H


#pragma once
#include <raylib.h>
#include "types.hpp"

#define ASSETS_PATH "./assets/"

namespace pk {

    // ASSETS
        constexpr char GRAPHICS_PATH[] = ASSETS_PATH "graphics/";
        constexpr char CHARACTERS_PATH[] = ASSETS_PATH "graphics/characters/";
        constexpr char OBJECTS_PATH[] = ASSETS_PATH "graphics/objects/";
        constexpr char FONTS_PATH[] = ASSETS_PATH "font/";
        constexpr char WINDOW_ICON[] = ASSETS_PATH "icon/window-icon.png";        

    // window
        constexpr unsigned int SCREEN_W = 1280;
        constexpr unsigned int SCREEN_H = 720;    
        constexpr float SCREEN_W_F = static_cast<float>(SCREEN_W);
        constexpr float SCREEN_H_F = static_cast<float>(SCREEN_H);
        constexpr float SCREEN_CENTERX = SCREEN_W_F / 2.0f;
        constexpr float SCREEN_CENTERY = SCREEN_H_F / 2.0f;
        constexpr Vector2 SCREEN_SIZE = Vector2{SCREEN_W_F, SCREEN_H_F};
        constexpr Vector2 SCREEN_CENTER = Vector2{SCREEN_CENTERX, SCREEN_CENTERY};
        constexpr char WINDOW_TITLE[] = "PokemonRpg";
        constexpr pk::SceneId FIRST_SCENE = pk::SceneId::TitleScreenId;
    
    // ECS
        constexpr pk::entity_t MAX_ENTITIES = 4096;

    // tiles
        constexpr float TILE_SIZE = 64.0f;
    
    // player
        constexpr float PLAYER_SPEED = 150.0f;
        constexpr Vector2 PLAYER_SIZE = Vector2{128.0f, 128.0f};
    
    // camera
        constexpr pk::zindex_t CAMERA_MIN_ZINDEX = 0;
        constexpr pk::zindex_t CAMERA_MAX_ZINDEX = 10;
    
} // namespace pk

#pragma once
#include <raylib.h>
#include <raymath.h>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <typeinfo>
#include <cstdint>
#include <stdio.h>
#include <cassert>
#include <memory>
#include <queue>
#include <array>
#include <cmath>
#include <map>


#define POKE_SCREEN_WIDTH (1280)
#define POKE_SCREEN_HEIGHT (720)
#define POKE_WINDOW_TITLE ("Pokemon")
#define POKE_TILE_SIZE (64)

#define POKE_MAX_ENTITIES (4096)

#define POKE_PLAYER_MOVEMENT_SPEED (200.0f)

#define POKE_PLAYER_WIDTH (128.0f)
#define POKE_PLAYER_HEIGHT (128.0f)
#define POKE_PLAYER_ANIMATION_SPEED (10)

#define POKE_ANIMATION_SPEED_SLOW (4)
#define POKE_ANIMATION_SPEED_NORMAL (6)
#define POKE_ANIMATION_SPEED_FAST (8)

#define POKE_GROUND_ZINDEX '0'
#define POKE_SHADOW_ZINDEX '1'
#define POKE_PLAYER_ZINDEX '2'


namespace poke {

	typedef std::uint32_t entity_t;
	typedef std::uint8_t component_t;
	
} // namespace poke


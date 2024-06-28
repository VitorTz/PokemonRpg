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

#define POKE_MAX_ENTITIES (4096)

#define POKE_PLAYER_MOVEMENT_SPEED (200.0f)


namespace poke {

	typedef std::uint8_t component_t;
	typedef std::uint32_t entity_t;
	typedef std::uint8_t zindex_t;
	typedef std::uint8_t tile_t;
	
} // namespace poke


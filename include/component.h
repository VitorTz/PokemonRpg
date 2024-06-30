#pragma once
#include "pokemon.h"
#include "texture_pool.h"


namespace poke {

	inline std::unordered_map<const char*, poke::component_t> gComponentTypeMap{};

	template<typename T>
	void registerType() {
		poke::gComponentTypeMap.insert(
			std::pair<const char*, poke::component_t>(
				typeid(T).name(), poke::gComponentTypeMap.size()
			)
		);
	}
	
	template<typename T>
	poke::component_t getType() {
		return poke::gComponentTypeMap.at(typeid(T).name());
	}	

	typedef struct transform {
		Vector2 pos{ 0 };
		Vector2 size{ 0 };
		char lastDirection[2]{ 'i', 'd' };
		char direction[2]{ 'i', 'd' };
		char zindex{ '0' };
		transform() = default;
		transform(const char _zindex) : zindex(_zindex) { }
	} transform_t;

	typedef struct rigid_body {
		Vector2 direction = { 0 };
		Vector2 lastMovement = { 0 };
		float speed{ 0.0f };
	} rigid_body_t;


	typedef struct sprite {
		Texture2D texture;
		Rectangle rect;
		sprite() = default;
		sprite(
			const char* file_name
		) : texture(poke::gTexturePool.load(file_name)),
			rect({0.0f, 0.0f, (float) texture.width, (float) texture.height}) {

		}
		sprite(
			const char* file_name,
			Vector2 size
		) : sprite(file_name) {
			this->rect.width = size.x;
			this->rect.height = size.y;
		} 
	} sprite_t;

	typedef struct sprite_animation {
		sprite_t sprite{};
		std::uint8_t speed{ 0 };
		std::uint8_t cols{ 0 };
		std::uint8_t currentFrame{ 0 };
		std::uint8_t currentSprite{ 0 };
		std::uint8_t maxSprites{ 0 };
		sprite_animation(
			const char* file_name,
			const int rows,
			const int cols,
			const int speed
		) : sprite(file_name),
			speed(60 / speed),
			cols(cols),
			maxSprites(rows * cols) {
			sprite.rect.width = (float)(sprite.texture.width / cols);
			sprite.rect.height = (float)(sprite.texture.height / rows);
		}
		sprite_animation() = default;
	} sprite_animation_t;

	typedef struct obstacle {
		Rectangle rect;
		Vector2 hitbox;
	} obstacle_t;

	typedef struct player {		
		poke::entity_t playerShadowEntity;
		std::uint8_t currentFrame{ 0 };
		std::uint8_t currentSprite{ 0 };
		std::uint8_t action{ 'x' };	
	} player_t;

}
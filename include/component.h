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
		Vector2 pos = { 0 };
		Vector2 size = { 0 };
		Vector2 direction = { 0 };
		poke::zindex_t zindex = 0;
		float speed = 0.0f;
		transform() = default;
		transform(const poke::zindex_t _zindex) : zindex(_zindex) { }
	} transform_t;


	typedef struct sprite {
		Texture2D texture;
		Rectangle rect;
		sprite() = default;
		sprite(
			const char* file_name
		) : texture(poke::gTexturePool.load(file_name)),
			rect({0.0f, 0.0f, (float) texture.width, (float) texture.height}) {
			
		}
	} sprite_t;

}
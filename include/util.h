#pragma once
#include "pokemon.h"


namespace poke {


	void print_vec(const Vector2 v);

	void print_rect(const Rectangle& r);

	unsigned long hash(const char* s);

	void applyCharacterSpriteRect(Rectangle* rect, const char direction[2], const std::uint8_t numSprite);


} // namespace poke
#pragma once
#include "ecs/components.hpp"

namespace pk {


    void mAssert(bool status, const char* msg);
    void mAssert(bool status);    
    
    void transformSetCenter(pk::transform_t& t, const sf::Vector2f& center);
    void transformPrint(const pk::transform_t& t);
    void normalizeVec(sf::Vector2f* vec);

    sf::Vector2f getDirection();
    
    sf::Vector2f getDirection(
        sf::Keyboard::Key left,
        sf::Keyboard::Key right,
        sf::Keyboard::Key up,
        sf::Keyboard::Key down
    );
    
} // namespace pk

#pragma once
#include "ecs/components.hpp"

namespace pk {


    void mAssert(bool status, const char* msg);
    void mAssert(bool status);    
    
    void transformSetCenter(pk::transform_t& t, const sf::Vector2f& center);
    
} // namespace pk

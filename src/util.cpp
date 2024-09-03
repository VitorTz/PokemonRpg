#include  "../include/util.hpp"
#include "../include/ecs/ECS.hpp"
#include <iostream>
#include <cstdlib>


void pk::mAssert(const bool status) {
    if (status == false) {
        std::exit(EXIT_FAILURE);
    }
}


void pk::mAssert(const bool status, const char* msg) {
    if (status == false) {
        std::cout << msg << '\n';
        std::exit(EXIT_FAILURE);
    }
}


void pk::transformSetCenter(pk::transform_t& t, const sf::Vector2f& center) {
    t.pos.x = center.x - t.size.x / 2.0f;
    t.pos.y = center.y - t.size.y / 2.0f;
}


void pk::transformPrint(const pk::transform_t& t) {
    std::cout << "Transform(" 
            << t.pos.x 
            << ',' 
            << ' ' 
            << t.pos.y 
            << ',' 
            << ' ' 
            << t.size.x 
            << ',' 
            << ' ' 
            << t.size.y 
            << ')' 
            << '\n';
}
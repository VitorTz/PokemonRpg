#include  "../include/util.hpp"
#include "../include/ecs/ECS.hpp"
#include <cmath>
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


void pk::normalizeVec(sf::Vector2f* vec) {
    const float m = std::sqrt(vec->x * vec->x + vec->y * vec->y);
    if (m > 1.0f) {
        vec->x /= m;
        vec->y /= m;
    }
}


sf::Vector2f pk::getDirection(
    const sf::Keyboard::Key left,
    const sf::Keyboard::Key right,
    const sf::Keyboard::Key up,
    const sf::Keyboard::Key down
) {
    sf::Vector2f direction{};
    
    if (sf::Keyboard::isKeyPressed(up)) {
        direction.y = -1.0f;
    } else if (sf::Keyboard::isKeyPressed(down)) {
        direction.y = 1.0f;
    }

    if (sf::Keyboard::isKeyPressed(left)) {
        direction.x = -1.0f;
    } else if (sf::Keyboard::isKeyPressed(right)) {
        direction.x = 1.0f;
    }

    pk::normalizeVec(&direction);
    return direction;
}


sf::Vector2f pk::getDirection() {
    return pk::getDirection(
        sf::Keyboard::A,
        sf::Keyboard::D,
        sf::Keyboard::W,
        sf::Keyboard::S
    );
}

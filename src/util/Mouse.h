//
// Created by vitor on 9/22/24.
//

#ifndef MOUSE_H
#define MOUSE_H
#include <SFML/System/Vector2.hpp>

namespace pk {

    class Mouse {

    public:
        bool isPressed{};
        bool isReleased{};
        sf::Vector2f mousePos{};
        sf::Vector2f mouseWorldPos{};

    public:
        void reset();

    };

    inline pk::Mouse gMouse{};

}

#endif //MOUSE_H

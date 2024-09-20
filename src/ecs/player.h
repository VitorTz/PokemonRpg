//
// Created by vitor on 9/20/24.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "components.h"


namespace pk {

    inline pk::player_t gPlayer{};

    void playerCreate();

    sf::Vector2f playerCenter();

}

#endif //PLAYER_H

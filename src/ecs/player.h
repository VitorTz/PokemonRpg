//
// Created by vitor on 10/1/24.
//
#ifndef PLAYER_H
#define PLAYER_H
#include "../pokemon.h"


namespace pk {

    typedef struct player_info {
        pk::entity_t playerEntity{};
        pk::entity_t shadowEntity{};
        Rectangle collisionRect{};
        char directionState[2]{'i', 'd'};
    } player_info_t;

}


#endif //PLAYER_H

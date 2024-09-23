//
// Created by vitor on 9/21/24.
//

#ifndef TYPES_H
#define TYPES_H
#include <cstdint>
#include <queue>
#include <vector>


namespace pk {

    typedef std::uint32_t entity_t;
    typedef std::uint8_t component_t;
    typedef std::uint8_t zindex_t;
    typedef struct sprite_animation_source {
        const char* filePath{};
        int spriteWidth{};
        int spriteHeight{};
        int rows{};
        int cols{};
        int speed{};
    } sprite_animation_source_t;

    typedef std::vector<std::pair<float, pk::entity_t>> EntityVector;

    typedef struct std::pair<double, std::pair<int, int>> pPair;
    typedef struct std::priority_queue<pPair, std::vector<pPair>, std::greater<>> PriorityQueue;


}

#endif //TYPES_H

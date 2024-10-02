//
// Created by vitor on 9/30/24.
//

#ifndef TYPES_H
#define TYPES_H
#include <cstdint>


namespace pk {

    typedef std::uint32_t entity_t;
    typedef std::uint8_t component_t;
    typedef std::uint8_t zindex_t;

    typedef struct tiled_map {
        const char* worldImage{};
        const char* txtFile{};
        Vector2 worldSize{};
        int rows{};
        int cols{};
    } tiled_map_t;

    typedef struct sprite_animation_source {
        const char* fileName{};
        std::uint8_t rows{};
        std::uint8_t cols{};
        std::uint8_t speed{};
    } sprite_animation_source_t;


}


#endif //TYPES_H

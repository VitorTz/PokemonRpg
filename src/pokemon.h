//
// Created by vitor on 9/14/24.
//

#ifndef POKEMON_H
#define POKEMON_H

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <memory>
#include <array>
#include <queue>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <typeinfo>
#include <cassert>


namespace pk {

    typedef std::uint32_t entity_t;
    typedef std::uint8_t component_t;
    typedef std::uint8_t zindex_t;
    typedef std::vector<std::pair<float, pk::entity_t>> OrderedEntityVector;
    typedef std::map<pk::zindex_t, pk::OrderedEntityVector> CameraMap;

    constexpr unsigned int SCREEN_W{1280};
    constexpr unsigned int SCREEN_H{720};
    constexpr char WINDOW_TITLE[]{"Pokemon Rpg"};
    constexpr float SCREEN_WF{static_cast<float>(SCREEN_W)};
    constexpr float SCREEN_HF{static_cast<float>(SCREEN_H)};
    constexpr float SCREEN_CENTERX{SCREEN_WF / 2.0f};
    constexpr float SCREEN_CENTERY{SCREEN_HF / 2.0f};

    constexpr pk::entity_t MAX_ENTITIES{4096};
    constexpr pk::zindex_t CAMERA_MIN_ZINDEX{0};
    constexpr pk::zindex_t CAMERA_MAX_ZINDEX{10};

    const static sf::Vector2f SCREEN_SIZE(pk::SCREEN_WF, pk::SCREEN_HF);
    const static sf::Vector2f SCREEN_CENTER(pk::SCREEN_CENTERX, pk::SCREEN_CENTERY);
    const static sf::FloatRect SCREEN_RECT(0.0f, 0.0f, SCREEN_WF, SCREEN_HF);


}

#endif //POKEMON_H

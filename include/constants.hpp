#pragma once
#include <SFML/Graphics.hpp>
#include "scene/SceneId.hpp"
#include "types.hpp"


namespace pk {

    constexpr unsigned int SCREEN_W{1280};
    constexpr unsigned int SCREEN_H{720};
    constexpr float SCREEN_W_F = static_cast<float>(pk::SCREEN_W);
    constexpr float SCREEN_H_F = static_cast<float>(pk::SCREEN_H);
    constexpr char WINDOW_TITLE[] = "PokemonRpg";
    constexpr pk::SceneId MAIN_SCENE{pk::SceneId::TitleScreenId};
    constexpr float SCREEN_CENTERX = pk::SCREEN_W_F / 2.0f;
    constexpr float SCREEN_CENTERY = pk::SCREEN_H_F / 2.0f;
    const static sf::Vector2f SCREEN_SIZE(pk::SCREEN_W_F, pk::SCREEN_H_F);
    const static sf::Vector2f SCREEN_CENTER(pk::SCREEN_CENTERX, pk::SCREEN_CENTERY);

    constexpr pk::entity_t MAX_ENTITIES{4096};
    constexpr float CAMERA_MIN_ZOON{0.25f};
    constexpr float CAMERA_MAX_ZOON{4.0f};

    constexpr pk::zindex_t ZINDEX_MIN{0};
    constexpr pk::zindex_t ZINDEX_MAX{10};

    
} // namespace pk

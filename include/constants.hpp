#pragma once
#include "scene/SceneId.hpp"


namespace pk {

    constexpr unsigned int SCREEN_W{1280};
    constexpr unsigned int SCREEN_H{720};
    constexpr float SCREEN_W_F = static_cast<float>(pk::SCREEN_W);
    constexpr float SCREEN_H_F = static_cast<float>(pk::SCREEN_H);
    constexpr char WINDOW_TITLE[] = "PokemonRpg";

    constexpr pk::SceneId MAIN_SCENE{pk::SceneId::TitleScreenId};
    
} // namespace pk

//
// Created by vitor on 9/28/24.
//

#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "types.h"
#include "../scene/SceneID.h"


#define ASSETS_PATH "./assets/"


namespace pk {

    constexpr float SCREEN_W{1280.0f};
    constexpr float SCREEN_H{720.0f};
    constexpr float SCREEN_CENTERX{SCREEN_W / 2.0f};
    constexpr float SCREEN_CENTERY{SCREEN_H / 2.0f};
    constexpr float WORLD_WIDTH{4096.0f};
    constexpr float WORLD_HEIGHT{4096.0f};
    constexpr char WINDOW_TITLE[]{"PokemonRpg"};

    constexpr pk::SceneId MAIN_SCENE{pk::SceneId::TitleScreenId};

    constexpr pk::entity_t MAX_ENTITIES{4096};

    constexpr pk::zindex_t CAMERA_MIN_ZINDEX{0};
    constexpr pk::zindex_t CAMERA_MAX_ZINDEX{10};
    constexpr float CAMERA_MIN_ZOOM{0.25f};
    constexpr float CAMERA_MAX_ZOOM{2.0f};

}


#endif //CONSTANTS_H

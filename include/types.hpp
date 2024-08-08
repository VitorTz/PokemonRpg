#pragma once
#include <cstdint>


namespace pk {

    typedef std::uint32_t entity_t;
    typedef std::uint8_t component_t;
    typedef std::uint8_t zindex_t;

    enum SceneId {
        TitleScreenId,
        LevelSceneId,
        LoadingSceneId
    };
    
} // namespace pk 

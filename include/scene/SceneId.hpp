#pragma once
#include <unordered_map>
#include <string>


namespace pk {

    enum SceneId {
        LevelSceneId,
        TitleScreenId,
    };

    const static std::unordered_map<pk::SceneId, std::string> sceneIdToString = {
        {pk::SceneId::LevelSceneId, "LevelScene"},
        {pk::SceneId::TitleScreenId, "TitleScreenScene"}
    };
    
} // namespace pk

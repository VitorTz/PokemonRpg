#pragma once
#include <unordered_map>
#include <string>


namespace pk {

    enum SceneId {
        LevelSceneId,
        TitleScreenId,
        TestScene1Id,
        SceneCount
    };

    const static std::unordered_map<pk::SceneId, std::string> sceneIdToString = {
        {pk::SceneId::LevelSceneId, "LevelScene"},
        {pk::SceneId::TitleScreenId, "TitleScreenScene"},
        {pk::SceneId::TestScene1Id, "TestScene1"}
    };
    
} // namespace pk

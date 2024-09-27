#pragma once
#include "AssetPool.hpp"
#include "../scene/Scene.hpp"
#include "Camera.hpp"
#include "types.hpp"


namespace pk {

    
    inline pk::AssetPool gAssetPool{};
    inline pk::TypeId gTypeId{};
    inline pk::SceneManager gSceneManager{};
    inline pk::Camera gCamera{};

}
//
// Created by vitor on 9/28/24.
//
#ifndef SCENE_H
#define SCENE_H
#include <array>
#include <raylib.h>
#include <memory>
#include <iostream>
#include "SceneID.h"
#include "../util/constants.h"


namespace pk {

    class Scene {

    public:
        virtual ~Scene() = default;
        virtual void update(float dt) = 0;
        virtual void draw() = 0;

    };

    class TitleScreen final : public pk::Scene {

    private:
        Texture2D background{};
        Texture2D logo{};
        Texture2D pressSpace{};
        std::array<Vector2, 2> backgroundPos{
            Vector2{0.0f, 0.0f},
            Vector2{pk::SCREEN_W, 0.0f}
        };

    public:
        TitleScreen();
        void update(float dt) override;
        void draw() override;

    };

    class LevelScene final : public pk::Scene {

    public:
        LevelScene();
        void update(float dt) override;
        void draw() override;

    };

    class LoadingScreen final : public pk::Scene {

    public:
        LoadingScreen();
        void update(float dt) override;
        void draw() override;

    };

    class SceneManager final : public pk::Scene {

    private:
        std::unique_ptr<pk::Scene> scene{};
        std::unique_ptr<pk::LoadingScreen> loadingScreen{};

    private:
        pk::SceneId sceneId{pk::MAIN_SCENE};
        bool shouldChangeScene{};
        bool isChangingScene{};

    private:
        void loadNextScene();

    public:
        void init();
        void changeScene(pk::SceneId sceneId);
        void update(float dt) override;
        void draw() override;

    };

    inline pk::SceneManager gSceneManager{};

}

#endif //SCENE_H

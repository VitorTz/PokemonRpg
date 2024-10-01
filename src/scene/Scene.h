//
// Created by vitor on 9/30/24.
//

#ifndef SCENE_H
#define SCENE_H
#include "../pokemon.h"


namespace pk {


    class Scene {

    public:
        virtual ~Scene() = default;
        virtual void update(float dt) = 0;
        virtual void draw() = 0;

    };

    class TitleScreen : public pk::Scene {

    public:
        TitleScreen();
        void update(float dt) override;
        void draw() override;

    };

    class LevelScene : public pk::Scene {

    public:
        LevelScene();
        void update(float dt) override;
        void draw() override;

    };

    class TestScene1 : public pk::Scene {

    public:
        TestScene1();
        void update(float dt) override;
        void draw() override;

    };

    class LoadingScene : public pk::Scene {

    public:
        LoadingScene();
        void update(float dt) override;
        void draw() override;

    };

    class SceneManager final : public pk::Scene {

    private:
        std::unique_ptr<pk::Scene> scene{};
        std::unique_ptr<pk::LoadingScene> loadingScene{};

    private:
        bool shouldChangeScene{};
        pk::SceneId sceneId{pk::MAIN_SCENE};

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

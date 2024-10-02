//
// Created by vitor on 9/30/24.
//

#ifndef SCENE_H
#define SCENE_H
#include "../pokemon.h"


namespace pk {


    class Scene {

    protected:
        std::unordered_map<pk::TiledMapId, int> ecsInstance{};

    public:
        virtual ~Scene() = default;
        virtual void update(float dt) = 0;
        virtual void draw() = 0;

    };

    class TitleScreen final : public pk::Scene {

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

    class TestScene1 final : public pk::Scene {

    public:
        TestScene1();
        void update(float dt) override;
        void draw() override;

    };

    class LoadingScene final : public pk::Scene {

    public:
        LoadingScene();
        void update(float dt) override;
        void draw() override;

    };

    class SceneManager final : public pk::Scene {

    private:
        std::unique_ptr<pk::Scene> scene{};
        std::unique_ptr<pk::LoadingScene> loadingScene{};
        bool shouldChangeScene{};
        pk::SceneId sceneId{pk::MAIN_SCENE};
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

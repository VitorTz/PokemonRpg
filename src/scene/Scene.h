//
// Created by vitor on 9/14/24.
//

#ifndef SCENE_H
#define SCENE_H
#include "../pokemon.h"
#include "../TexturePool.h"
#include "../util.h"
#include "../ecs/ECS.h"


namespace pk {


    class Scene {

    public:
        virtual ~Scene() = default;
        virtual void update(float dt) = 0;
        virtual void render(sf::RenderWindow& window) = 0;

    };


    class TitleScreen final : public pk::Scene {

    public:
        TitleScreen();
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;

    };

    class LevelScene final : public pk::Scene {

    public:
        LevelScene();
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;

    };

    class LoadingScreen final : public pk::Scene {

    public:
        LoadingScreen();
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;

    };

    class TestScene1 final : public pk::Scene {

    public:
        TestScene1();
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;

    };

    class SceneManager final : public pk::Scene {

    private:
        std::unique_ptr<pk::Scene> scene{};
        std::unique_ptr<pk::LoadingScreen> loadingScreen{};
        pk::SceneId nextScene{pk::MAIN_SCENE};
        bool shouldChangeScene{};
        bool isChangingScene{};

    private:
        void loadNextScene();

    public:
        void init();
        void update(float dt) override;
        void changeScene(pk::SceneId sceneId);
        void render(sf::RenderWindow& window) override;

    };

    inline pk::SceneManager gSceneManager{};

}

#endif //SCENE_H

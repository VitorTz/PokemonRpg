//
// Created by vitor on 9/21/24.
//

#ifndef SCENE_H
#define SCENE_H
#include "SceneID.h"
#include "../pokemon.h"
#include "../util/TiledMap.h"


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

    class Level final : public pk::Scene {

    private:
        std::unique_ptr<pk::TiledMap> tiledMap{};

    public:
        Level();
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

    private:
        std::unique_ptr<pk::TiledMap> tiledMap{};
        std::vector<std::pair<int, int>> walkPath{};

    public:
        TestScene1();
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;

    };

    class SceneManager final : public pk::Scene {

    private:
        std::unique_ptr<pk::Scene> scene{};
        std::unique_ptr<pk::LoadingScreen> loadingScreen{};
        pk::SceneId sceneId{pk::MAIN_SCENE};
        bool shouldChangeScene{false};
        bool isChangingScene{false};

    private:
        void loadNextScene();

    public:
        void init();
        void changeScene(pk::SceneId sceneId);
        void update(float dt) override;
        void render(sf::RenderWindow& window) override;

    };

    inline pk::SceneManager gSceneManager{};

}

#endif //SCENE_H

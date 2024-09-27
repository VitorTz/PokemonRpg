#pragma once
#include <memory>
#include "../util/constants.hpp"


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


    class LoadingScene : public pk::Scene {

        public:
            LoadingScene();
            void update(float dt) override;
            void draw() override;

    };


    class TestScene1 : public pk::Scene {

        public:
            TestScene1();
            void update(float dt) override;
            void draw() override;

    };


    class SceneManager : public pk::Scene {

        private:
            std::unique_ptr<pk::Scene> scene{};
            std::unique_ptr<pk::LoadingScene> loadingScene{};
            pk::SceneId nextScene{pk::MAIN_SCENE};

        private:
            bool shouldChangeScene{false};
            bool isChangingScene{false};

        private:
            void loadNextScene();

        public:            
            void init();
            void changeScene(pk::SceneId sceneId);
            void update(float dt) override;
            void draw() override;

    };

}
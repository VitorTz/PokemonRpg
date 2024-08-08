#pragma once
#include <raylib.h>
#include <stdio.h>
#include <memory>
#include "TexturePool.hpp"
#include "constants.hpp"
#include "types.hpp"


namespace pk  {    

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

    class SceneManager : public pk::Scene {

        private:
            std::unique_ptr<pk::Scene> scene{};
            std::unique_ptr<pk::LoadingScene> loadingScene{};
            pk::SceneId sceneId{};
            bool isChangingScene{};
            bool shouldChangeScene{};
        
        private:
            void loadNextScene();

        public:            
            void changeScene(pk::SceneId sceneId);
            void init();
            void update(float dt) override;
            void draw() override;

    };

    inline pk::SceneManager gSceneManager{};
    
} // namespace pk 

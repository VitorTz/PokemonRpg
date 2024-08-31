#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../constants.hpp"
#include "SceneId.hpp"


namespace pk {

    class Scene {

        public:
            virtual ~Scene() = default;
            virtual void update(float dt) = 0;
            virtual void draw(sf::RenderWindow& window) = 0;

    };

    class LoadingScreen : public pk::Scene {

        public:
            LoadingScreen();
            void update(float dt) override;
            void draw(sf::RenderWindow& window) override;

    };

    class Level : public pk::Scene {

        public:
            Level();
            void update(float dt) override;
            void draw(sf::RenderWindow& window) override;

    };

    class TitleScreen : public pk::Scene {

        public:
            TitleScreen();
            void update(float dt) override;
            void draw(sf::RenderWindow& window) override;

    };

    class SceneManager : public pk::Scene {

        private:
            std::unique_ptr<pk::Scene> scene{};
            std::unique_ptr<pk::LoadingScreen> loadingScreen{};

        private:
            pk::SceneId nextScene{pk::MAIN_SCENE};
            bool shouldChangeScene{};
        
        private:
            void loadNextScene();
    
        public:
            void init();
            void changeScene(pk::SceneId sceneId);     
            void update(float dt) override;
            void draw(sf::RenderWindow& window) override;

    };  

    inline pk::SceneManager gSceneManager{};
    
} // namespace pk

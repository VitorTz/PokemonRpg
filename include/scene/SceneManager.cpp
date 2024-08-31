#include "Scene.hpp"


void pk::SceneManager::init() {
    this->loadNextScene();
    this->loadingScreen = std::make_unique<pk::LoadingScreen>();
}


void pk::SceneManager::loadNextScene() {
    switch (this->nextScene) {
        case pk::SceneId::TitleScreenId:
            this->scene = std::make_unique<pk::TitleScreen>();
            break;
        case pk::SceneId::LevelSceneId:
            this->scene = std::make_unique<pk::Level>();
            break;        
        default:
            break;
    }
}

void pk::SceneManager::changeScene(const pk::SceneId sceneId) {
    this->shouldChangeScene = true;
    this->nextScene = sceneId;
}


void pk::SceneManager::update(const float dt) {
    this->scene->update(dt);
    if (this->shouldChangeScene) {
        this->shouldChangeScene = false;
        this->loadNextScene();
    }
}


void pk::SceneManager::draw(sf::RenderWindow& window) {
    this->scene->draw(window);
}
#include "../include/Scene.hpp"
#include <thread>


void pk::SceneManager::init() {
    this->sceneId = pk::FIRST_SCENE;
    this->loadNextScene();
    this->loadingScene = std::make_unique<pk::LoadingScene>();
}


void pk::SceneManager::loadNextScene() {    
    switch (this->sceneId) {
        case pk::SceneId::TitleScreenId:
            this->scene = std::make_unique<pk::TitleScreen>();
            break;
        case pk::SceneId::LevelSceneId:
            this->scene = std::make_unique<pk::LevelScene>();
        case pk::SceneId::LoadingSceneId:
            this->scene = std::make_unique<pk::LoadingScene>();
        default:
            break;
    }
    this->isChangingScene = false;
}


void pk::SceneManager::changeScene(const pk::SceneId nextSceneId) {
    if (
        this->isChangingScene == false &&
        this->shouldChangeScene == false
    ) {
        this->sceneId = nextSceneId;
        this->shouldChangeScene = true;
    }
}


void pk::SceneManager::update(const float dt) {
    if (this->isChangingScene) {
        this->loadingScene->update(dt);
        return;    
    }
    this->scene->update(dt);
    if (this->shouldChangeScene) {
        this->shouldChangeScene = false;
        this->isChangingScene = true;
        std::thread t(&pk::SceneManager::loadNextScene, this);
        t.detach();
    }
}


void pk::SceneManager::draw() {
    if (this->isChangingScene) {
        this->loadingScene->draw();
    } else {
        this->scene->draw();
    }
}
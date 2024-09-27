#include "Scene.hpp"
#include <thread>


void pk::SceneManager::init() {
    this->loadNextScene();
    this->loadingScene = std::make_unique<pk::LoadingScene>();
}


void pk::SceneManager::loadNextScene() {
    switch (this->nextScene) {
        case pk::SceneId::TestScene1Id:
            this->scene = std::make_unique<pk::TestScene1>();
            break;
        case pk::SceneId::LevelSceneId:
            this->scene = std::make_unique<pk::LevelScene>();
            break;
        case pk::SceneId::TitleScreenId:
            this->scene = std::make_unique<pk::TitleScreen>();
            break;
        case pk::SceneId::LoadingSceneId:
            this->scene = std::make_unique<pk::LoadingScene>();
            break;
        default:
            break;
    }
    this->isChangingScene = false;
}


void pk::SceneManager::changeScene(const pk::SceneId sceneId) {
    if (this->isChangingScene == false) {
        this->shouldChangeScene = true;
        this->nextScene = sceneId;
    }
}


void pk::SceneManager::update(const float dt) {
    if (this->isChangingScene) {
        this->loadingScene->update(dt);
    } else {
        this->scene->update(dt);
    }
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
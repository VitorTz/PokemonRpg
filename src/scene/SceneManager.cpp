//
// Created by vitor on 9/30/24.
//
#include "Scene.h"


void pk::SceneManager::init() {
    this->loadNextScene();
    this->loadingScene = std::make_unique<pk::LoadingScene>();
}


void pk::SceneManager::loadNextScene() {
    switch (this->sceneId) {
        case pk::SceneId::LevelSceneId:
            this->scene = std::make_unique<pk::LevelScene>();
            break;
        case pk::SceneId::TitleScreenId:
            this->scene = std::make_unique<pk::TitleScreen>();
            break;
        case pk::SceneId::TestScene1Id:
            this->scene = std::make_unique<pk::TestScene1>();
            break;
        default:
            break;
    }
}


void pk::SceneManager::changeScene(const pk::SceneId sceneId) {
    this->sceneId = sceneId;
    this->shouldChangeScene = true;
}


void pk::SceneManager::update(const float dt) {
    this->scene->update(dt);
    if (this->shouldChangeScene) {
        this->loadNextScene();
        this->shouldChangeScene = false;
    }
}


void pk::SceneManager::draw() {
    this->scene->draw();
}

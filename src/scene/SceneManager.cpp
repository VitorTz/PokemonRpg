//
// Created by vitor on 9/28/24.
//
#include "Scene.h"
#include <thread>


void pk::SceneManager::init() {
    this->loadNextScene();
    this->loadingScreen = std::make_unique<pk::LoadingScreen>();
}


void pk::SceneManager::loadNextScene() {
    this->isChangingScene = true;
    switch (this->sceneId) {
        case pk::SceneId::TitleScreenId:
            this->scene = std::make_unique<pk::TitleScreen>();
            break;
        case pk::SceneId::LevelScreenId:
            this->scene = std::make_unique<pk::LevelScene>();
            break;
        default:
            break;
    }
    this->isChangingScene = false;
}


void pk::SceneManager::changeScene(const pk::SceneId sceneId) {
    if (this->isChangingScene == false) {
        this->shouldChangeScene = true;
        this->sceneId = sceneId;
    }
}


void pk::SceneManager::update(const float dt) {
    if (this->isChangingScene) {
        this->loadingScreen->update(dt);
    } else {
        this->scene->update(dt);
    }
    if (this->shouldChangeScene) {
        this->shouldChangeScene = false;
        std::thread t(&pk::SceneManager::loadNextScene, this);
        t.detach();
    }
}


void pk::SceneManager::draw() {
    if (this->isChangingScene) {
        this->loadingScreen->draw();
    } else {
        this->scene->draw();
    }
}


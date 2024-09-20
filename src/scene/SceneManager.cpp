//
// Created by vitor on 9/14/24.
//
#include "Scene.h"
#include "../util/Debug.h"


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
            this->scene = std::make_unique<pk::LevelScene>();
            break;
        case pk::SceneId::LoadingScreenId:
            this->scene = std::make_unique<pk::LoadingScreen>();
            break;
        case pk::SceneId::TestScene1Id:
            this->scene = std::make_unique<pk::TestScene1>();
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
    if (this->isChangingScene == true) {
        this->loadingScreen->update(dt);
    } else {
        this->scene->update(dt);
    }
    if (this->shouldChangeScene == true) {
        this->isChangingScene = true;
        this->shouldChangeScene = false;
        std::thread t(&pk::SceneManager::loadNextScene, this);
        t.detach();
    }
}


void pk::SceneManager::render(sf::RenderWindow &window) {
    if (this->isChangingScene == true) {
        this->loadingScreen->render(window);
    } else {
        this->scene->render(window);
        if (pk::DEBUG_MODE) {
            pk::gDebug.draw(window);
        }
    }
}


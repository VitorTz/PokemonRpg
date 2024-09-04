#include "../../include/scene/Scene.hpp"


void pk::SceneManager::init() {
    std::cout << "[Iniciando SceneManager]\n";
        pk::mAssert(pk::sceneIdToString.size() == pk::SceneId::SceneCount, "[Size invalid! -> sceneIdToString]");
        this->loadNextScene();
        this->loadingScreen = std::make_unique<pk::LoadingScreen>();
    std::cout << "[SceneManager iniciado]\n";
}


void pk::SceneManager::loadNextScene() {
    std::cout << "[LOADING NEXT SCENE] -> " << pk::sceneIdToString.at(this->nextScene) << '\n';
    switch (this->nextScene) {
        case pk::SceneId::TitleScreenId:
            this->scene = std::make_unique<pk::TitleScreen>();
            break;
        case pk::SceneId::LevelSceneId:
            this->scene = std::make_unique<pk::Level>();
            break;
        case pk::SceneId::TestScene1Id:
            this->scene = std::make_unique<pk::TestScene1>();
            break;
        default:
            break;
    }
    std::cout << "[SCENE LOADED] -> " << pk::sceneIdToString.at(this->nextScene) << '\n';
}

void pk::SceneManager::changeScene(const pk::SceneId sceneId) {
    std::cout << "[CHANGE SCENE REQUEST] -> " << pk::sceneIdToString.at(sceneId) << '\n';
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
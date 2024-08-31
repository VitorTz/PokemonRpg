#include "../../include/scene/Scene.hpp"


pk::TitleScreen::TitleScreen() {
    
}


void pk::TitleScreen::update(const float dt) {
    pk::gSceneManager.changeScene(pk::SceneId::LevelSceneId);    
}


void pk::TitleScreen::draw(sf::RenderWindow& window) {
    
}
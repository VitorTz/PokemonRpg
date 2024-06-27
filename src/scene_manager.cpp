#include "../include/scene_manager.h"


void poke::SceneManager::init() {
	this->loadNextScene();
}

void poke::SceneManager::loadNextScene() {
	switch (this->nextSceneId) {
	case poke::TitleScreenId:
		this->scene = std::make_unique<poke::TitleScreen>();
		break;
	case poke::LevelScreenId:
		this->scene = std::make_unique<poke::LevelScreen>();
		break;
	default:
		break;
	}
}


void poke::SceneManager::changeScene(const poke::SceneId sceneId) {
	this->shouldChangeScene = true;
	this->nextSceneId = sceneId;
}


void poke::SceneManager::update() {
	this->scene->update();
}


void poke::SceneManager::draw() {
	this->scene->draw();
	if (this->shouldChangeScene) {
		this->shouldChangeScene = false;
		this->loadNextScene();
	}
}

#pragma once
#include "scene.h"


namespace poke {


	class SceneManager {
			
	private:
		std::unique_ptr<poke::Scene> scene;
		bool shouldChangeScene = false;
		poke::SceneId nextSceneId = poke::LevelScreenId;

	private:
		void loadNextScene();

	public:		
		void init();
		void changeScene(poke::SceneId sceneId);
		void update();
		void draw();

	};

	inline poke::SceneManager gSceneManager{};

}
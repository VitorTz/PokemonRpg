#pragma once
#include "pokemon.h"


namespace poke {

	enum SceneId {
		TitleScreenId,
		LevelScreenId
	};

	class Scene {

	public:
		virtual ~Scene() = default;
		virtual void update() = 0;
		virtual void draw() = 0;

	};


	class TitleScreen : public poke::Scene {

	public:
		TitleScreen();
		void update() override;
		void draw() override;

	};

	class BattleScene : public poke::Scene {

	public:
		BattleScene();
		void setUpBattle();
		void update() override;
		void draw() override;

	};

	class LevelScreen : public poke::Scene {

	private:
		bool battle;
		poke::BattleScene battleScene{};

	public:
		LevelScreen();
		void update() override;
		void draw() override;

	};

}
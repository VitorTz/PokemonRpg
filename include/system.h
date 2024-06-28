#pragma once
#include "pokemon.h"


namespace poke {


	class System {

	public:
		std::unordered_set<poke::entity_t> entities;

	public:
		virtual ~System() = default;
		virtual void update(float dt) = 0;
		virtual void draw(poke::entity_t e) = 0;

	};


	class TransformSystem : public poke::System {
	
	public:		
		void update(float dt) override;
		void draw(poke::entity_t e) override;

	};

	class RigidBodySystem : public poke::System {

	public:
		void update(float dt) override;
		void draw(const poke::entity_t e) override;

	};

	class SpriteSystem : public poke::System {

	public:
		void update(float dt) override;
		void draw(poke::entity_t e) override;

	};


	class ObstacleSystem : public poke::System {
	
	public:
		void update(float dt) override;
		void draw(poke::entity_t e) override;

	};

	class PlayerSystem : public poke::System {

	public:
		void update(float dt) override;
		void draw(const poke::entity_t e);

	};

}
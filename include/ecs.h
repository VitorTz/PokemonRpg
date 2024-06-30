#pragma once
#include "entity_manager.h"
#include "component_manager.h"
#include "system_manager.h"


namespace poke {


	class ECS {

	private:
		std::queue<poke::entity_t> entitiesToDestroy{};
		bool shouldDestroyAllEntities = false;

	private:
		std::map<char, std::vector<std::pair<float, poke::entity_t>>> camera{};
		std::array<bool, POKE_MAX_ENTITIES> isOnCamera{};
	
	private:
		poke::EntityManager entity{};
		poke::ComponentManager component{};
		poke::SystemManager system{};

	public:
		
		void init() {
			
			// register Component
			poke::registerType<poke::transform_t>();
			poke::registerType<poke::rigid_body_t>();
			poke::registerType<poke::sprite_t>();
			poke::registerType<poke::sprite_animation_t>();
			poke::registerType<poke::obstacle_t>();
			poke::registerType<poke::player_t>();

			// register ComponentArray
			this->component.registerComponentArray<poke::transform_t>();
			this->component.registerComponentArray<poke::sprite_t>();
			this->component.registerComponentArray<poke::rigid_body_t>();
			this->component.registerComponentArray<poke::obstacle_t>();
			this->component.registerComponentArray<poke::sprite_animation_t>();
			this->component.registerComponentArray<poke::player_t>();
				
			// register System
			this->system.registerSystem<poke::transform_t, poke::TransformSystem>();
			this->system.registerSystem<poke::rigid_body_t, poke::RigidBodySystem>();			
			this->system.registerSystem<poke::sprite_t, poke::SpriteSystem>();
			this->system.registerSystem<poke::sprite_animation_t, poke::SpriteAnimationSystem>();
			this->system.registerSystem<poke::obstacle_t, poke::ObstacleSystem>();
			this->system.registerSystem<poke::player_t, poke::PlayerSystem>();

			// Init Camera
			for (char i = '0'; i <= '9'; i++) {
				this->camera.insert({ i, {} });
				this->camera[i].reserve(POKE_MAX_ENTITIES);
			}

		}

		poke::entity_t entityCreate(const char zindex, const bool isOnCamera) {
			const poke::entity_t e = this->entity.entityCreate();
			this->addComponent<poke::transform_t>(e, poke::transform_t{zindex});
			if (isOnCamera) this->submitToCamera(e, zindex);
			return e;
		}

		void submitToCamera(const poke::entity_t e, const char zindex) {
			if (this->isOnCamera[e] == false) {
				this->isOnCamera[e] = true;
				this->camera[zindex].push_back(std::make_pair(0.0f, e));
			}
		}

		void rmvFromCamera(const poke::entity_t e) {
			if (this->isOnCamera[e] == true) {
				this->isOnCamera[e] = false;
				const char z = this->component.at<poke::transform_t>(e).zindex;
				std::vector<std::pair<float, poke::entity_t>>& v = this->camera[z];
				for (std::size_t i = 0; i < v.size(); i++) {
					if (v[i].second == e) {
						v.erase(v.begin() + i);
						return;
					}
				}
			}
		}

		void entityDestroy(const poke::entity_t e) {
			this->entitiesToDestroy.push(e);
		}

		template<typename T>
		void addComponent(poke::entity_t e, T c) {
			this->component.insert<T>(e, c);
			this->system.addToSystem<T>(e);
		}

		template<typename T>
		void rmvComponent(poke::entity_t e) {
			this->component.erase<T>(e);
			this->system.rmvFromSystem<T>(e);
		}

		template<typename T>
		T& getComponent(const poke::entity_t e) {
			return this->component.at<T>(e);
		}

		template<typename T>
		void addToSystem(const poke::entity_t e) {
			this->system.addToSystem<T>(e);
		}

		template<typename T>
		void rmvFromSystem(const poke::entity_t e) {
			this->system.rmvFromSystem<T>(e);
		}

		poke::transform_t& getTransform(const poke::entity_t e) {
			return this->component.at<poke::transform_t>(e);
		}

		template<typename T>
		const std::unordered_set<poke::entity_t>* getEntitiesBySystem() {
			return this->system.getEntitiesBySystem<T>();
		}

		void clear() {
			this->shouldDestroyAllEntities = true;
		}

		void update(const float dt) {
			this->system.update(dt);			

			if (this->shouldDestroyAllEntities) {
				this->shouldDestroyAllEntities = false;
				this->entitiesToDestroy = std::queue<poke::entity_t>();
				for (auto& pair : this->camera) {
					pair.second.clear();
				}
				for (bool& b : this->isOnCamera) {
					b = false;
				}				
				this->entity.clear();
				this->component.clear();
				this->system.clear();
			}

			while (this->entitiesToDestroy.empty() == false) {
				const poke::entity_t e = this->entitiesToDestroy.front();
				this->entitiesToDestroy.pop();
				this->rmvFromCamera(e);
				this->entity.entityDestroy(e);
				this->component.entityDestroy(e);
				this->system.entityDestroy(e);
			}

		}
		
		void draw() {
			for (auto& pair : this->camera) {
				for (std::pair<float, poke::entity_t>& e : pair.second) {
					const poke::transform_t& t = this->component.at<poke::transform_t>(e.second);
					e.first = t.pos.y + t.size.y / 2.0f;
				}
				std::sort(pair.second.begin(), pair.second.end());
				for (const std::pair<float, poke::entity_t>& e : pair.second) {
					this->system.draw(e.second);
				}
			}			

		}

		std::size_t numEntitiesAlive() const {
			return this->entity.size();
		}		

	};

	inline poke::ECS gEcs;

}
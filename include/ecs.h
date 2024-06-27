#pragma once
#include "entity_manager.h"
#include "component_manager.h"
#include "system_manager.h"


namespace poke {


	class ECS {

	private:
		std::queue<poke::entity_t> entitiesToDestroy;
		bool shouldDestroyAllEntities = false;

	private:
		std::map<poke::zindex_t, std::vector<std::pair<float, poke::entity_t>>> camera{};
		std::array<bool, POKE_MAX_ENTITIES> isOnCamera{};
	
	private:
		poke::EntityManager entity;
		poke::ComponentManager component;
		poke::SystemManager system;

	public:
		
		void init() {
			
			poke::registerType<poke::transform_t>();
			poke::registerType<poke::sprite_t>();

			this->component.registerComponentArray<poke::transform_t>();
			this->component.registerComponentArray<poke::sprite_t>();
			
			this->system.registerSystem<poke::transform_t, poke::TransformSystem>();
			this->system.registerSystem<poke::sprite_t, poke::SpriteSystem>();

		}

		poke::entity_t entityCreate(const poke::zindex_t zindex, const bool isOnCamera) {
			const poke::entity_t e = this->entity.entityCreate();
			this->addComponent<poke::transform_t>(e, poke::transform_t{});
			if (isOnCamera) this->submitToCamera(e, zindex);
			return e;
		}

		void submitToCamera(const poke::entity_t e, poke::zindex_t zindex) {
			if (this->isOnCamera[e] == false) {
				this->isOnCamera[e] = true;
				this->camera[zindex].push_back(std::pair<float, poke::entity_t>{0.0f, e});
			}
		}

		void rmvFromCamera(const poke::entity_t e) {
			if (this->isOnCamera[e] == true) {
				this->isOnCamera[e] = false;
				const poke::zindex_t z = this->component.at<poke::transform_t>(e).zindex;
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

		poke::transform_t getTransform(const poke::entity_t e) {
			return this->component.at<poke::transform_t>(e);
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

	};

	inline poke::ECS gEcs;

}
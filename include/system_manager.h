#pragma once
#include "pokemon.h"
#include "component.h"
#include "system.h"


namespace poke {


	class SystemManager {

	private:
		std::unordered_map<poke::component_t, std::unique_ptr<poke::System>> systemMap;
		std::unordered_map<poke::entity_t, std::unordered_set<poke::component_t>> systemByEntity;

	public:
		SystemManager() {
			this->systemByEntity.reserve(POKE_MAX_ENTITIES);
		}

		template<typename T, typename E>
		void registerSystem() {
			this->systemMap.emplace(
				poke::getType<T>(),
				std::make_unique<E>()
			);
		}

		template<typename T>
		void addToSystem(const poke::entity_t e) {
			const poke::component_t id = poke::getType<T>();
			this->systemMap[id]->entities.insert(e);
			this->systemByEntity[e].insert(id);
			
		}

		template<typename T>
		void rmvFromSystem(const poke::entity_t e) {
			const poke::component_t id = poke::getType<T>();
			this->systemMap[id]->entities.erase(e);
			this->systemByEntity[e].erase(id);
		}

		template<typename T>
		const std::unordered_set<poke::entity_t>* getEntitiesBySystem() {
			return &this->systemMap[poke::getType<T>()]->entities;
		}

		void entityDestroy(const poke::entity_t e) {
			for (auto& pair : this->systemMap) {
				pair.second->entities.erase(e);
			}
		}

		void clear() {
			for (auto& pair : this->systemMap) {
				pair.second->entities.clear();
			}
		}

		void update(const float dt) {
			for (auto& pair : this->systemMap) {
				pair.second->update(dt);
			}
		}

		void draw(const poke::entity_t e) {
			for (const poke::component_t id : this->systemByEntity[e]) {
				this->systemMap[id]->draw(e);
			}
		}

	};

}
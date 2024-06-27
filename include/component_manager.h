#pragma once
#include "pokemon.h"
#include "component_array.h"
#include "component.h"


namespace poke {


	class ComponentManager {

	private:
		std::unordered_map<poke::component_t, std::unique_ptr<poke::IComponentArray>> componentMap;				

	private:
		template<typename T>
		poke::ComponentArray<T>* getArray() {
			return dynamic_cast<poke::ComponentArray<T>*>(this->componentMap.at(poke::getType<T>()).get());
		}

	public:		

		template<typename T>
		void registerComponentArray() {
			this->componentMap.emplace(
				poke::getType<T>(),
				std::make_unique<poke::ComponentArray<T>>()
			);
		}

		void entityDestroy(const poke::entity_t e) {
			for (auto& pair : this->componentMap) {
				pair.second->erase(e);
			}
		}

		template<typename T>
		void insert(const poke::entity_t e, T c) {
			return this->getArray<T>()->insert(e, std::move(c));
		}

		template<typename T>
		T& at(const poke::entity_t e) {
			return this->getArray<T>()->at(e);
		}

		template<typename T>
		void erase(const poke::entity_t e) {
			this->componentMap[poke::getType<T>()]->erase(e);
		}

		void clear() {
			for (auto& pair : this->componentMap) {
				pair.second->clear();
			}
		}

		template<typename T>
		std::size_t size() const {
			return this->componentMap.at(poke::getType<T>())->size();
		}
		

	};


}
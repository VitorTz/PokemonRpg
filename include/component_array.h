#pragma once
#include "pokemon.h"


namespace poke {


	class IComponentArray {

	public:
		virtual ~IComponentArray() = default;
		virtual bool erase(poke::entity_t e) = 0;
		virtual void clear() = 0;
		virtual std::size_t size() const = 0;

	};

	template<typename T>
	class ComponentArray : public poke::IComponentArray {

	private:
		std::array<T, POKE_MAX_ENTITIES> arr{};
		std::unordered_map<poke::entity_t, std::size_t> entityToIndex;
		std::unordered_map<std::size_t, poke::entity_t> indexToEntity;
		std::size_t mSize = 0;

	public:
		ComponentArray() {
			this->entityToIndex.reserve(POKE_MAX_ENTITIES);
			this->indexToEntity.reserve(POKE_MAX_ENTITIES);			
		}

		void insert(const poke::entity_t e, T c) {
			assert(this->mSize < POKE_MAX_ENTITIES);
			this->entityToIndex[e] = this->mSize;
			this->indexToEntity[this->mSize] = e;
			this->arr[this->mSize++] = c;
		}

		bool erase(const poke::entity_t e) override {
			if (this->entityToIndex.find(e) != this->entityToIndex.end()) {
				const std::size_t lastComponentIndex = --this->mSize;
				const std::size_t removedComponentIndex = this->entityToIndex[e];
				const poke::entity_t lastEntity = this->indexToEntity[lastComponentIndex];
			
				this->arr[removedComponentIndex] = this->arr[lastComponentIndex];
			
				this->entityToIndex[lastEntity] = removedComponentIndex;
				this->indexToEntity[removedComponentIndex] = lastEntity;

				this->entityToIndex.erase(e);
				this->indexToEntity.erase(lastComponentIndex);

				return true;				
			}
			return false;
;		}

		T& at(const poke::entity_t e) {
			assert(this->entityToIndex.find(e) != this->entityToIndex.end());
			return this->arr[this->entityToIndex[e]];
		}

		void clear() override {
			this->entityToIndex.clear();
			this->indexToEntity.clear();
			this->mSize = 0;
		}

		std::size_t size() const override {
			return this->mSize;
		}

	};

}

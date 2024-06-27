#pragma once
#include "pokemon.h"


namespace poke {


	class EntityManager {

	private:
		std::queue<poke::entity_t> queue;
		std::size_t mSize = 0;

	public:
		EntityManager();
		poke::entity_t entityCreate();
		void entityDestroy(poke::entity_t e);
		void clear();
		std::size_t size() const;

	};

}
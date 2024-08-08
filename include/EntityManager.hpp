#pragma once
#include <queue>
#include "EcsManager.hpp"
#include "constants.hpp"


namespace pk  {

    class EntityManager : public pk::EcsManager {

        private:
            std::queue<pk::entity_t> queue;
            std::size_t mSize{};

        public:
            EntityManager();
            pk::entity_t entityCreate();
            void entityDestroy(pk::entity_t e) override;
            void clear() override;
            std::size_t size() const override;

    };

    
} // namespace pk 

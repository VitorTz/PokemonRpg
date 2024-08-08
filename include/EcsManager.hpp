#pragma once
#include "types.hpp"



namespace pk {

    class EcsManager {

        public:
            virtual ~EcsManager() = default;            
            virtual void entityDestroy(pk::entity_t e) = 0;
            virtual void clear() = 0;
            virtual std::size_t size() const = 0;

    };
    
} // namespace pk

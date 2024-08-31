#pragma once
#include <unordered_map>
#include <typeinfo>
#include "types.hpp"


namespace pk {

    class TypeId {

        private:
            std::unordered_map<const char*, pk::component_t> typeIdMap{};
        
        public:
            template<typename T>
            void registerId() {
                this->typeIdMap.insert(
                    {typeid(T).name(), this->typeIdMap.size()}
                );
            }
            
            template<typename T>
            pk::component_t get() {
                return this->typeIdMap[typeid(T).name()];
            }
            
            std::size_t size() const {
                return this->typeIdMap.size();
            }

    };

    inline pk::TypeId gTypeId{};
    
} // namespace pk

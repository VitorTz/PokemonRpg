#pragma once
#include <unordered_map>
#include <typeinfo>
#include <cassert>
#include "types.hpp"


namespace pk {


    inline std::unordered_map<const char*, pk::component_t> gComponentIdMap{};

    template<typename T>
    void registerComponent() {
        const char* typeName = typeid(T).name();
        assert(
            pk::gComponentIdMap.find(typeName) == pk::gComponentIdMap.end() &&
            "Component already registered"
        );
        pk::gComponentIdMap.insert({typeName, pk::gComponentIdMap.size()});
    }


    template<typename T>
    pk::component_t getId() {
        return pk::gComponentIdMap[typeid(T).name()];
    }    
    
} // namespace pk

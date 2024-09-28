//
// Created by vitor on 9/28/24.
//

#ifndef TYPEID_H
#define TYPEID_H
#include <typeinfo>
#include <unordered_map>
#include "types.h"


namespace pk {


    class TypeId {

    private:
        std::unordered_map<const char*, pk::component_t> typeMap{};

    public:
        template<typename T>
        void registerType() {
            this->typeMap.emplace(typeid(T).name(), this->typeMap.size());
        }

        template<typename T>
        pk::component_t get() {
            return this->typeMap[typeid(T).name()];
        }

        std::size_t size() const {
            return this->typeMap.size();
        }

    };

    inline pk::TypeId gTypeId{};


}

#endif //TYPEID_H

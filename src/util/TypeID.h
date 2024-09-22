//
// Created by vitor on 9/21/24.
//

#ifndef TYPEID_H
#define TYPEID_H
#include <typeinfo>
#include <unordered_map>
#include "types.h"


namespace pk {

    class TypeID {

    private:
        std::unordered_map<const char*, pk::component_t> idMap{};

    public:
        template<typename T>
        void registerType() {
            this->idMap[typeid(T).name()] = this->idMap.size();
        }

        template<typename T>
        pk::component_t get() const {
            return this->idMap.at(typeid(T).name());
        }

        std::size_t size() const {
            return this->idMap.size();
        }

    };

    inline pk::TypeID gTypeId{};

}

#endif //TYPEID_H

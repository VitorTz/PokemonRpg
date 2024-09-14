//
// Created by vitor on 9/14/24.
//

#ifndef TYPEID_H
#define TYPEID_H
#include "pokemon.h"
#include "ecs/components.h"

namespace pk {

    class TypeId {

    private:
        std::unordered_map<const char*, pk::component_t> typeMap{};

    public:
        TypeId() {
            this->typeMap.emplace(typeid(pk::transform_t).name(), this->typeMap.size());
            this->typeMap.emplace(typeid(pk::sprite_t).name(), this->typeMap.size());
            this->typeMap.emplace(typeid(pk::collision_box_t).name(), this->typeMap.size());
            this->typeMap.emplace(typeid(pk::collision_box_static_t).name(), this->typeMap.size());
            this->typeMap.emplace(typeid(pk::water_t).name(), this->typeMap.size());
            assert(this->typeMap.size() == pk::NUM_COMPONENTS);
        }

        template<typename T>
        pk::component_t get() const {
            return this->typeMap.at(typeid(T).name());
        }

    };

    inline pk::TypeId gTypeId{};

}



#endif //TYPEID_H


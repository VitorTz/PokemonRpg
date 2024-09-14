//
// Created by vitor on 9/14/24.
//

#ifndef COMPONENTARRAY_H
#define COMPONENTARRAY_H
#include "../pokemon.h"

namespace pk {

    class IComponentArray {

    public:
        virtual ~IComponentArray() = default;
        virtual void erase(pk::entity_t e) = 0;
        virtual void clear() = 0;
        virtual std::size_t size() const = 0;
    };


    template<typename T>
    class ComponentArray : public pk::IComponentArray {

    private:
        std::array<T, pk::MAX_ENTITIES> arr{};
        std::unordered_map<pk::entity_t, std::size_t> entityToIndex{};
        std::unordered_map<std::size_t, pk::entity_t> indexToEntity{};
        std::size_t mSize{};

    public:
        ComponentArray();
        void insert(pk::entity_t e, T c);
        void erase(pk::entity_t e) override;
        T& at(pk::entity_t e);
        void clear() override;
        std::size_t size() const override;

    };

}



#endif //COMPONENTARRAY_H

//
// Created by vitor on 9/14/24.
//

#ifndef ENTITYMANAGE_H
#define ENTITYMANAGE_H
#include "../pokemon.h"

namespace pk {

    class EntityManager {

    private:
        std::queue<pk::entity_t> entities{};
        std::size_t mSize{};

    public:
        EntityManager();
        pk::entity_t entityCreate();
        void entityDestroy(pk::entity_t e);
        void clear();
        std::size_t size() const;

    };

}

#endif //ENTITYMANAGE_H

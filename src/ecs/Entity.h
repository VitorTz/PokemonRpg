//
// Created by vitor on 9/28/24.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <queue>
#include "../util/constants.h"


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


#endif //ENTITY_H

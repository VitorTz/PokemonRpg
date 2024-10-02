//
// Created by vitor on 9/30/24.
//

#ifndef ENTITY_H
#define ENTITY_H
#include "EcsManager.h"
#include "../pokemon.h"

namespace pk {

    class EntityManager final : public pk::EcsManager {

    private:
        std::queue<pk::entity_t> q{};
        std::size_t mSize{};

    public:
        explicit EntityManager(const pk::TiledMapId mapId);
        pk::entity_t entityCreate();
        void entityDestroy(pk::entity_t e) override;
        void clear() override;
        std::size_t size() const;

    };

}

#endif //ENTITY_H

//
// Created by vitor on 10/1/24.
//

#ifndef ECSMANAGER_H
#define ECSMANAGER_H
#include "../util/TiledMapId.h"
#include "../util/types.h"


namespace pk {

    class EcsManager {

    protected:
        const pk::TiledMapId mapId;

    public:
        explicit EcsManager(const pk::TiledMapId mapId) : mapId(mapId) { }
        virtual ~EcsManager() = default;
        virtual void entityDestroy(pk::entity_t e) = 0;
        virtual void clear() = 0;

    };

}

#endif //ECSMANAGER_H

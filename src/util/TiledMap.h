//
// Created by vitor on 9/30/24.
//

#ifndef TILEDMAP_H
#define TILEDMAP_H
#include "../pokemon.h"


namespace pk {

    class TiledMap {

    private:
        std::unordered_map<pk::TiledMapId, pk::tiled_map_t> maps{};
        std::unordered_map<pk::TiledMapId, std::unordered_set<int>> invalidTiles{};
        pk::TiledMapId currentMap{};

    public:
        pk::TiledMapId getIdOfCurrentMap() const;
        void setCurrentMapId(pk::TiledMapId mapId);
        void loadMap(pk::TiledMapId mapId);
        void unloadMap(pk::TiledMapId mapId);
        const pk::tiled_map_t& getTiledMap(pk::TiledMapId mapId) const;
        const pk::tiled_map_t& getCurrentTiledMap() const;

    };

    inline pk::TiledMap gTiledMap{};

}



#endif //TILEDMAP_H

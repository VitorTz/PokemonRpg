//
// Created by vitor on 9/29/24.
//

#ifndef TILED_MAP_H
#define TILED_MAP_H
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <memory>


namespace pk {

    enum TiledMapId {
        WorldMapId
    };

    class TiledMap {

    private:
        typedef struct tiled_map {
            std::string dir{};
            std::size_t rows{};
            std::size_t cols{};
            std::unordered_set<int> invalidTiles{};
            tiled_map() = default;
            explicit tiled_map(const char* dir) : dir(dir) { }
        } tiled_map_t;

    private:
        std::unordered_map<pk::TiledMapId, std::unique_ptr<pk::TiledMap::tiled_map_t>> tiledMaps{};

    public:
        TiledMap();
        void loadMap(pk::TiledMapId mapId);
        void unloadMap(pk::TiledMapId mapId);
        void isValidTile(pk::TiledMapId mapId, int tile);

    };

    inline pk::TiledMap gTiledMap{};

}


#endif //TILED_MAP_H

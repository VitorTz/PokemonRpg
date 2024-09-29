//
// Created by vitor on 9/29/24.
//
#include "TiledMap.h"
#include "constants.h"


pk::TiledMap::TiledMap() {
    this->tiledMaps.emplace(
        pk::TiledMapId::WorldMapId,
        std::make_unique<pk::TiledMap::tiled_map_t>(ASSETS_PATH "graphics/map/world-map")
    );
}


void pk::TiledMap::loadMap(const pk::TiledMapId mapId) {

}


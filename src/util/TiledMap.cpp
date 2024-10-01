//
// Created by vitor on 9/30/24.
//
#include "TiledMap.h"


void pk::TiledMap::loadMap(const pk::TiledMapId mapId) {
    assert(this->maps.find(mapId) == this->maps.end());
    this->maps.emplace(mapId, pk::tiled_map_t{});
    this->invalidTiles.emplace(mapId, std::unordered_set<int>());

    pk::tiled_map_t& tiledMap = this->maps[mapId];
    std::unordered_set<int>& invalidTiles = this->invalidTiles[mapId];

    std::string txtFile{pk::MAP_PATH[mapId]};
    txtFile += "map.txt";
    std::ifstream file(txtFile);
    assert(file.is_open());

    int n;
    file >> tiledMap.width >> tiledMap.height >> tiledMap.rows >> tiledMap.cols;
    file >> n;
    invalidTiles.reserve(n);
    for (int i = 0; i < n; i++) {
        int tile;
        file >> tile;
        invalidTiles.insert(tile);
    }
    file.close();
}


void pk::TiledMap::unloadMap(const pk::TiledMapId mapId) {
    this->maps.erase(mapId);
    this->invalidTiles.erase(mapId);
}


const pk::tiled_map_t &pk::TiledMap::getTiledMap(const pk::TiledMapId mapId) const {
    assert(this->maps.find(mapId) != this->maps.end());
    return this->maps.at(mapId);
}


const pk::tiled_map_t& pk::TiledMap::getCurrentTiledMap() const {
    return this->getTiledMap(this->currentMap);
}


pk::TiledMapId pk::TiledMap::getIdOfCurrentMap() const {
    return this->currentMap;
}


void pk::TiledMap::setCurrentMapId(const pk::TiledMapId mapId) {
    this->currentMap = mapId;
}


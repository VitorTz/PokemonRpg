#include "AssetPool.hpp"
#include "raylib.h"
#include "util.hpp"


pk::AssetPool::AssetPool() {
    this->texturePool.reserve(256);
}


Texture2D pk::AssetPool::getTexture(const char* fileName) {
    const unsigned long h = pk::hash(fileName);
    if (this->texturePool.find(h) == this->texturePool.end()) {
        this->texturePool.emplace(h, LoadTexture(fileName));
    }
    return this->texturePool[h];
}


void pk::AssetPool::erase(const char* fileName) {
    const unsigned long h = pk::hash(fileName);
    if (this->texturePool.find(h) != this->texturePool.end()) {
        UnloadTexture(this->texturePool[h]);
        this->texturePool.erase(h);
    }    
}


void pk::AssetPool::clear() {
    for (auto& pair : this->texturePool) {
        UnloadTexture(pair.second);
    }
    this->texturePool.clear();
}


std::size_t pk::AssetPool::textureSize() const {
    return this->texturePool.size();
}


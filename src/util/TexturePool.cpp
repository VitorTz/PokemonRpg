//
// Created by vitor on 9/28/24.
//
#include "TexturePool.h"
#include "util.h"


pk::TexturePool::TexturePool() {
    this->texturePool.reserve(256);
}


Texture2D pk::TexturePool::get(const char *fileName) {
    const pk::hash_t h = pk::hash(fileName);
    if (this->texturePool.find(h) == this->texturePool.end()) {
        this->texturePool.emplace(h, LoadTexture(fileName));
    }
    return this->texturePool[h];
}


void pk::TexturePool::clear() {
    for (auto& pair : this->texturePool) {
        UnloadTexture(pair.second);
    }
    this->texturePool.clear();
}


std::size_t pk::TexturePool::size() const {
    return this->texturePool.size();
}



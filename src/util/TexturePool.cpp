//
// Created by vitor on 9/30/24.
//
#include "TexturePool.h"
#include "util.h"


pk::TexturePool::TexturePool() {
    this->texturePool.reserve(256);
}


Texture2D pk::TexturePool::load(const char *fileName) {
    const unsigned long h = pk::hash(fileName);
    if (this->texturePool.find(h) == this->texturePool.end()) {
        this->texturePool.emplace(h, LoadTexture(fileName));
    }
    return this->texturePool[h];
}


void pk::TexturePool::clear() {
    for (const auto& pair : this->texturePool) {
        UnloadTexture(pair.second);
    }
}


std::size_t pk::TexturePool::size() const {
    return this->texturePool.size();
}

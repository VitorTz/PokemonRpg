#include "../include/TexturePool.hpp"
#include "../include/util.hpp"


pk::TexturePool::TexturePool() {
    this->textureMap.reserve(256);
}


Texture2D pk::TexturePool::load(const char* fileName) {
    const unsigned long h = pk::hash(fileName);
    if (this->textureMap.find(h) == this->textureMap.end()) {
        this->textureMap.insert({h, LoadTexture(fileName)});
    }
    return this->textureMap[h];
}


void pk::TexturePool::erase(const char* fileName) {
    const unsigned long h = pk::hash(fileName);
    if (this->textureMap.find(h) != this->textureMap.end()) {
        UnloadTexture(this->textureMap[h]);
    }
    this->textureMap.erase(h);
}


void pk::TexturePool::clear() {
    for (auto& pair : this->textureMap) {
        UnloadTexture(pair.second);
    }
    this->textureMap.clear();
}


std::size_t pk::TexturePool::size() const {
    return this->textureMap.size();
}
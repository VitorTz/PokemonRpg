//
// Created by vitor on 9/14/24.
//
#include "TexturePool.h"
#include "util.h"

pk::TexturePool::TexturePool() {
    this->textureMap.reserve(256);
}


sf::Sprite pk::TexturePool::get(const char *fileName) {
    sf::Sprite sprite{};
    const unsigned long h = pk::hash(fileName);
    if (this->textureMap.find(h) == this->textureMap.end()) {
        const bool s = this->textureMap[h].loadFromFile(fileName);
        assert(s && "[IMAGE NOT LOADING]");
        std::cout << "[IMAGE LOADED! -> " << fileName << ']' << '\n';
    }
    sprite.setTexture(this->textureMap[h]);
    return sprite;
}


void pk::TexturePool::set(sf::Sprite *sprite, const char *fileName) {
    const unsigned long h = pk::hash(fileName);
    if (this->textureMap.find(h) == this->textureMap.end()) {
        const bool s = this->textureMap[h].loadFromFile(fileName);
        assert(s && "[IMAGE NOT LOADING]");
    }
    sprite->setTexture(this->textureMap[h]);
}


void pk::TexturePool::erase(const char *fileName) {
    this->textureMap.erase(pk::hash(fileName));
}



void pk::TexturePool::clear() {
    this->textureMap.clear();
}


std::size_t pk::TexturePool::size() const {
    return this->textureMap.size();
}



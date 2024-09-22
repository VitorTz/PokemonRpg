//
// Created by vitor on 9/21/24.
//
#include <cassert>
#include "AssetPool.h"
#include "util.h"


pk::TexturePool::TexturePool() {
    this->pool.reserve(256);
}


sf::Sprite pk::TexturePool::get(const char *s) {
    sf::Sprite sprite{};
    const unsigned long h = pk::hash(s);
    if (this->pool.find(h) == this->pool.end()) {
        assert(this->pool[h].loadFromFile(s));
    }
    sprite.setTexture(this->pool[h]);
    return sprite;
}


void pk::TexturePool::erase(const char *s) {
    this->pool.erase(pk::hash(s));
}


void pk::TexturePool::clear() {
    this->pool.clear();
}


std::size_t pk::TexturePool::size() const {
    return this->pool.size();
}






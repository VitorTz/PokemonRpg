#include "../include/TexturePool.hpp"
#include "../include/util.hpp"
#include <iostream>


sf::Sprite pk::TexturePool::get(const char* filePath) {
    sf::Sprite sprite{};
    const unsigned long h = std::hash<const char*>{}(filePath);
    if (this->textureMap.find(h) == this->textureMap.end()) {        
        const bool status = this->textureMap[h].loadFromFile(filePath);
        std::cout << "[TEXTURE LOAD] -> [" << filePath << "] | Status: " << status << '\n';
        pk::mAssert(status, "[TEXTURE LOAD FAILED]");        
    }
    sprite.setTexture(this->textureMap[h]);
    return sprite;
}


void pk::TexturePool::erase(const char* filePath) {
    const unsigned long h = std::hash<const char*>{}(filePath);
    this->textureMap.erase(h);
}


std::size_t pk::TexturePool::size() const {
    return this->textureMap.size();
}


void pk::TexturePool::clear() {
    this->textureMap.clear();
}
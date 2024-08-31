#include "../include/TexturePool.hpp"
#include "../include/util.hpp"


sf::Sprite pk::TexturePool::get(const char* filePath) {
    const unsigned long h = std::hash<const char*>{}(filePath);
    sf::Sprite sprite{};
    if (this->textureMap.find(h) == this->textureMap.end()) {        
        this->textureMap[h].loadFromFile(filePath);
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
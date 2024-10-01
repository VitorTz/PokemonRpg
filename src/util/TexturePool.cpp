//
// Created by vitor on 9/30/24.
//
#include "TexturePool.h"
#include "util.h"


pk::TexturePool::TexturePool() {
    this->texturePool.reserve(256);
    this->loadQueue.reserve(32);
}


Texture2D pk::TexturePool::load(const char *fileName) {
    const unsigned long h = pk::hash(fileName);
    if (this->texturePool.find(h) == this->texturePool.end()) {
        this->texturePool.emplace(h, LoadTexture(fileName));
    }
    return this->texturePool[h];
}


void pk::TexturePool::addToAsyncLoad(const char *fileName) {
    std::cout << "[Image " << fileName << " ADDED TO ASYNC LOAD]\n";
    this->loadQueue.emplace_back(std::string{fileName}, Image{});
}



void pk::TexturePool::startAsyncLoad() {
    this->state = pk::Running;
    std::thread t(
        [this]() {
            for (std::pair<std::string, Image>& pair : this->loadQueue) {
                pair.second = LoadImage(pair.first.c_str());
            }
            this->state = pk::Completed;
        }
    );
    t.detach();
}


pk::AsyncLoadState pk::TexturePool::getAsyncLoadState() const {
    return this->state;
}


void pk::TexturePool::endAsyncLoad() {
    for (const std::pair<std::string, Image>& pair : this->loadQueue) {
        this->texturePool.emplace(pk::hash(pair.first.c_str()), LoadTextureFromImage(pair.second));
        UnloadImage(pair.second);
    }
    this->loadQueue.clear();
    this->state = pk::Idle;
}





void pk::TexturePool::unloadAll() {
    for (const auto& pair : this->texturePool) {
        UnloadTexture(pair.second);
    }
    this->texturePool.clear();
    for (const auto& pair : this->loadQueue) {
        UnloadImage(pair.second);
    }
    this->loadQueue.clear();
}


std::size_t pk::TexturePool::size() const {
    return this->texturePool.size();
}

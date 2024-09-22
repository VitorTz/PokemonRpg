//
// Created by vitor on 9/21/24.
//

#include "AssetPool.h"


sf::Text pk::FontPool::get(const pk::FontID fontId) {
    sf::Text text{};
    if (this->pool.find(fontId) == this->pool.end()) {
        this->pool[fontId].loadFromFile(pk::FONT_PATH[fontId]);
    }
    text.setFont(this->pool[fontId]);
    return text;
}


void pk::FontPool::set(sf::Text *text, const pk::FontID fontId) {
    if (this->pool.find(fontId) == this->pool.end()) {
        this->pool[fontId].loadFromFile(pk::FONT_PATH[fontId]);
    }
    text->setFont(this->pool[fontId]);
}


void pk::FontPool::clear() {
    this->pool.clear();
}


std::size_t pk::FontPool::size() const {
    return this->pool.size();
}



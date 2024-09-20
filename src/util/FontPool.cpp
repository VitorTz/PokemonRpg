//
// Created by vitor on 9/20/24.
//
#include "FontPool.h"


pk::FontPool::FontPool() {
    this->fontMap[pk::FontId::Light].loadFromFile(FONTS_PATH "Lato-Light.ttf");
    this->fontMap[pk::FontId::Regular].loadFromFile(FONTS_PATH "Lato-Regular.ttf");
    this->fontMap[pk::FontId::Bold].loadFromFile(FONTS_PATH "Lato-Bold.ttf");
}


void pk::FontPool::set(sf::Text *text, const pk::FontId fontId) const {
    text->setFont(this->fontMap.at(fontId));
}


void pk::FontPool::clear() {
    this->fontMap.clear();
}



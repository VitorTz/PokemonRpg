//
// Created by vitor on 9/21/24.
//

#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "FontID.h"


namespace pk {

    class TexturePool {

    private:
        std::unordered_map<unsigned long, sf::Texture> pool{};

    public:
        TexturePool();
        sf::Sprite get(const char* s);
        void erase(const char* s);
        void clear();
        std::size_t size() const;

    };

    class FontPool {

    private:
        std::unordered_map<pk::FontID, sf::Font> pool{};

    public:
        sf::Text get(pk::FontID fontId);
        void set(sf::Text* text, pk::FontID fontId);
        void clear();
        std::size_t size() const;

    };

    inline pk::TexturePool gTexturePool{};
    inline pk::FontPool gFontPool{};


}

#endif //OBJECTPOOL_H

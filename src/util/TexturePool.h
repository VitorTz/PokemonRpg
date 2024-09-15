//
// Created by vitor on 9/14/24.
//

#ifndef TEXTUREPOOL_H
#define TEXTUREPOOL_H
#include "../pokemon.h"

namespace pk {

    class TexturePool {

    private:
        std::unordered_map<unsigned long, sf::Texture> textureMap{};

    public:
        TexturePool();
        sf::Sprite get(const char* fileName);
        void set(sf::Sprite* sprite, const char* fileName);
        void erase(const char* fileName);
        void clear();
        std::size_t size() const;

    };

    inline pk::TexturePool gTexturePool{};

}

#endif //TEXTUREPOOL_H

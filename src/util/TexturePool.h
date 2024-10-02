//
// Created by vitor on 9/30/24.
//

#ifndef TEXTUREPOOL_H
#define TEXTUREPOOL_H
#include "../pokemon.h"


namespace pk {

    enum AsyncLoadState {
        Idle,
        Running,
        Completed
    };

    class TexturePool {

    private:
        std::unordered_map<unsigned long, Texture2D> texturePool{};

    public:
        TexturePool();
        Texture2D load(const char* fileName);
        void clear();
        std::size_t size() const;

    };

    inline pk::TexturePool gTexturePool{};

}

#endif //TEXTUREPOOL_H

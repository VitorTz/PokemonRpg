//
// Created by vitor on 9/28/24.
//

#ifndef TEXTUREPOOL_H
#define TEXTUREPOOL_H
#include <raylib.h>
#include <unordered_map>


namespace pk {

    class TexturePool {

    private:
        std::unordered_map<unsigned long, Texture2D> texturePool{};

    public:
        TexturePool();
        Texture2D get(const char* fileName);
        void clear();
        std::size_t size() const;

    };

    inline pk::TexturePool gTexturePool{};

}

#endif //TEXTUREPOOL_H

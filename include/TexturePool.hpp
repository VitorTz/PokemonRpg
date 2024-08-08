#pragma once
#include <raylib.h>
#include <unordered_map>


namespace pk {


    class TexturePool {

        private:
            std::unordered_map<unsigned long, Texture2D> textureMap{};
        
        public:
            TexturePool();
            Texture2D load(const char* fileName);
            void erase(const char* fileName);
            void clear();
            std::size_t size() const;

    };

    inline pk::TexturePool gTexturePool{};
    
} // namespace pk

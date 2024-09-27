#pragma once
#include <cstddef>
#include <raylib.h>
#include <unordered_map>


namespace pk {

    class AssetPool {

        private:
            std::unordered_map<unsigned long, Texture2D> texturePool{};            
        
        public:
            AssetPool();
            Texture2D getTexture(const char* fileName);
            void erase(const char* fileName);
            void clear();
            std::size_t textureSize() const;
        
    };

}
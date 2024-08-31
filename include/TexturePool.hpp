#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>


namespace pk {

    class TexturePool {

        private:
            std::unordered_map<std::size_t, sf::Texture> textureMap{};
        
        public:
            sf::Sprite get(const char* filePath);
            void erase(const char* filePath);
            void clear();
            std::size_t size() const;

    };

    inline pk::TexturePool gTexturePool{};
    
} // namespace pk

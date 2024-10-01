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
        std::vector<std::pair<std::string, Image>> loadQueue{};
        pk::AsyncLoadState state{pk::Idle};

    public:
        TexturePool();

        void startAsyncLoad();
        void addToAsyncLoad(const char* fileName);
        pk::AsyncLoadState getAsyncLoadState() const;
        void endAsyncLoad();

        Texture2D load(const char* fileName);
        void unloadAll();
        std::size_t size() const;

    };

    inline pk::TexturePool gTexturePool{};

}

#endif //TEXTUREPOOL_H

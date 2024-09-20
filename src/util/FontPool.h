//
// Created by vitor on 9/20/24.
//

#ifndef FONTPOOL_H
#define FONTPOOL_H
#include "../pokemon.h"


namespace pk {

    class FontPool {

    private:
        std::unordered_map<pk::FontId, sf::Font> fontMap{};

    public:
        FontPool();
        void set(sf::Text* text, pk::FontId fontId) const;
        void clear();
    };

    inline pk::FontPool gFontPool{};

}

#endif //FONTPOOL_H

//
// Created by vitor on 9/20/24.
//

#ifndef DEBUG_H
#define DEBUG_H
#include "../pokemon.h"
#include "FontPool.h"


namespace pk {

    class Debug {

    private:
        sf::Text text{};

    public:
        Debug();

    public:
        void draw(sf::RenderWindow& window);

    };

    inline pk::Debug gDebug{};

}



#endif //DEBUG_H

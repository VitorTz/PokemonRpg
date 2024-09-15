//
// Created by vitor on 9/14/24.
//

#ifndef WINDOW_H
#define WINDOW_H
#include "../pokemon.h"


namespace pk {

    class Window {

    private:
        sf::RenderWindow window{};
        sf::Clock clock{};

    private:
        void close();
        void handleEvents(float dt);
        void update(float dt);
        void render();

    public:
        Window();
        void mainloop();

    };

}

#endif //WINDOW_H

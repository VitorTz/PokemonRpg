//
// Created by vitor on 9/14/24.
//
#include "pokemon.h"
#include "scene/Scene.h"


void exit_game() {
    pk::gTexturePool.clear();
}


int main() {
    std::atexit(exit_game);
    // window
        sf::RenderWindow window(
            sf::VideoMode(pk::SCREEN_W, pk::SCREEN_H),
            pk::WINDOW_TITLE,
            sf::Style::Close | sf::Style::Titlebar
        );
        sf::Clock clock{};
        window.setVerticalSyncEnabled(true);

    // game init
        pk::gEcs.init();
        pk::gSceneManager.init();

    // mainloop
    while (window.isOpen()) {
        const float dt = clock.restart().asSeconds();

        // check events
            sf::Event e{};
            while (window.pollEvent(e)) {
                switch (e.type) {
                    case sf::Event::Closed:
                        window.close();
                        break;
                    case sf::Event::MouseWheelMoved:
                        pk::gCamera.addZoom(dt * static_cast<float>(e.mouseWheel.delta));
                        break;
                    default:
                        break;
                }
            }

        // update
            pk::gSceneManager.update(dt);
        // render
            window.clear();
            pk::gSceneManager.render(window);
            window.display();
    }
    exit_game();
}

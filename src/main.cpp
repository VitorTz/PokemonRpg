#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/scene/Scene.hpp"
#include "../include/constants.hpp"
#include "../include/TexturePool.hpp"


int main() {
    sf::RenderWindow window(
        sf::VideoMode(pk::SCREEN_W, pk::SCREEN_H),
        pk::WINDOW_TITLE,
        sf::Style::Close | sf::Style::Titlebar
    );
    window.setVerticalSyncEnabled(true);
    sf::Clock clock{};
    
    pk::gSceneManager.init();

    while (window.isOpen()) {
        const float dt = clock.restart().asSeconds();
        sf::Event e{};
        while (window.pollEvent(e)) {
            switch (e.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }

        window.clear();        
        window.display();
    }
    
    return 0;
}

//
// Created by vitor on 9/14/24.
//
#include "pokemon.h"

int main() {
    sf::RenderWindow window(
        sf::VideoMode(pk::SCREEN_W, pk::SCREEN_H),
        pk::WINDOW_TITLE,
        sf::Style::Close | sf::Style::Titlebar
    );
    sf::Clock clock{};
    window.setVerticalSyncEnabled(true);

    while (window.isOpen()) {
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
}

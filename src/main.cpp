#include "pokemon.h"
#include "ecs/ECS.h"
#include "scene/Scene.h"


int main() {
    sf::RenderWindow window(
        sf::VideoMode(pk::SCREEN_W, pk::SCREEN_H),
        pk::WINDOW_TITLE,
        sf::Style::Close | sf::Style::Titlebar
    );
    window.setVerticalSyncEnabled(true);
    sf::Clock clock{};

    const sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(
        sf::Vector2i(
            static_cast<int>(desktop.width) / 2 - static_cast<int>(pk::SCREEN_CENTERX),
            static_cast<int>(desktop.height) / 2 - static_cast<int>(pk::SCREEN_CENTERY)
        )
    );

    pk::gEcs.init();
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
        pk::gSceneManager.update(dt);
        window.clear();
        pk::gSceneManager.render(window);
        window.display();
    }

    return 0;
}

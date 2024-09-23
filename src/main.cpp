#include "pokemon.h"
#include "ecs/ECS.h"
#include "scene/Scene.h"


void exit_game() {
    pk::gTexturePool.clear();
    pk::gFontPool.clear();
}


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
        pk::gMouse.reset();
        pk::gMouse.mousePos = static_cast<sf::Vector2f>((sf::Mouse::getPosition(window)));
        pk::gMouse.mouseWorldPos = pk::gCamera.getMousePos(window);
        while (window.pollEvent(e)) {
            switch (e.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    pk::gMouse.isPressed = true;
                    break;
                case sf::Event::MouseButtonReleased:
                    pk::gMouse.isReleased = true;
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
    exit_game();
    return 0;
}

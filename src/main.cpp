#include "../include/ecs/ECS.hpp"
#include "../include/scene/Scene.hpp"
#include "../include/constants.hpp"
#include "../include/TexturePool.hpp"
#include "../include/Input.hpp"


void exit_game() {
    std::cout << "[EXITING GAME]\n";
    pk::gTexturePool.clear();
}


int main() {
    std::atexit(exit_game);

    // SFML
        sf::RenderWindow window(
            sf::VideoMode(pk::SCREEN_W, pk::SCREEN_H),
            pk::WINDOW_TITLE,
            sf::Style::Close | sf::Style::Titlebar
        );
        window.setVerticalSyncEnabled(true);
        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        window.setPosition(
            sf::Vector2i(
                desktop.width / 2 - pk::SCREEN_W / 2,
                desktop.height / 2 - pk::SCREEN_H / 2
            )
        );
        sf::Clock clock{};
    
    // Game
        pk::gEcs.init();
        pk::gSceneManager.init();

    // mainloop
        while (window.isOpen()) {
            pk::gInput.resetMouseWheelStatus();
            const float dt = clock.restart().asSeconds();
            // check events
                sf::Event e{};
                while (window.pollEvent(e)) {
                    if (e.type == sf::Event::Closed) {
                        window.close();
                    }
                    pk::gInput.handleEvent(e);
                }

            // update
                pk::gSceneManager.update(dt);
            
            // draw
                window.clear();
                pk::gSceneManager.draw(window);
                window.display();
                
        }
        
    return 0;
}

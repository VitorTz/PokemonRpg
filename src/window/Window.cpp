//
// Created by vitor on 9/14/24.
//
#include "Window.h"
#include "../scene/Scene.h"
#include "../ecs/ECS.h"
#include "Camera.h"


pk::Window::Window(
) : window(
    sf::VideoMode(pk::SCREEN_W, pk::SCREEN_H),
    pk::WINDOW_TITLE,
    sf::Style::Close | sf::Style::Titlebar
) {
    this->window.setVerticalSyncEnabled(true);
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(
        sf::Vector2i(
            desktop.width / 2 - pk::SCREEN_W / 2,
            desktop.height / 2 - pk::SCREEN_H / 2
        )
    );
    sf::Image iconImage{};
    iconImage.loadFromFile(ASSETS_PATH "data/icon/icon.png");
    window.setIcon(iconImage.getSize().x, iconImage.getSize().y, iconImage.getPixelsPtr());
    pk::gEcs.init();
    pk::gSceneManager.init();
}

void pk::Window::handleEvents(const float dt) {
    sf::Event e{};
    while (this->window.pollEvent(e)) {
        switch (e.type) {
            case sf::Event::Closed:
                this->window.close();
                break;
            case sf::Event::MouseWheelMoved:
                pk::gCamera.addZoom(dt * static_cast<float>(e.mouseWheel.delta));
                break;
            default:
                break;
        }
    }
}


void pk::Window::update(const float dt) {
    pk::gSceneManager.update(dt);
}


void pk::Window::render() {
    window.clear();
    pk::gSceneManager.render(this->window);
    window.display();
}


void pk::Window::close() {
    pk::gTexturePool.clear();
}


void pk::Window::mainloop() {
    while (this->window.isOpen()) {
        const float dt = this->clock.restart().asSeconds();
        this->handleEvents(dt);
        this->update(dt);
        this->render();
    }
    this->close();
}




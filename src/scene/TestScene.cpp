//
// Created by vitor on 9/21/24.
//
#include "Scene.h"
#include "../ecs/ECS.h"
#include "../util/TiledMap.h"


pk::TestScene1::TestScene1() {
    this->tiledMap = std::make_unique<pk::TiledMap>(ASSETS_PATH "map/world_map.txt");
    pk::gEcs.createPlayer();
}


void pk::TestScene1::update(const float dt) {
    pk::gEcs.update(dt);
    if (pk::gMouse.isPressed) {
        this->walkPath = tiledMap->getPath(pk::TiledMap::getPlayerTile(), pk::TiledMap::getTilePressedByMouse());
    }
}


void pk::TestScene1::render(sf::RenderWindow &window) {
    pk::gEcs.draw(window);
    pk::gCamera.beginDrawing(window);
    // Print walk path
    sf::RectangleShape rect(sf::Vector2f(16.f, 16.f));
    for (std::size_t i = 0; i < this->walkPath.size(); i++) {
        const auto& pair = this->walkPath[i];
        rect.setPosition(pair.first * 16.0f, pair.second * 16.0f);
        i == 0 || i == this->walkPath.size() - 1 ? rect.setFillColor(sf::Color::Green) : rect.setFillColor(sf::Color::Red);
        window.draw(rect);
    }
    pk::gCamera.endDrawing(window);
}


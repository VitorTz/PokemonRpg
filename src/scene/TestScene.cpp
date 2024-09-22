//
// Created by vitor on 9/21/24.
//
#include "Scene.h"
#include "../ecs/ECS.h"
#include "../util/TiledMap.h"


std::unique_ptr<pk::TiledMap> tiledMap{};
std::vector<std::pair<int, int>> path{};

pk::TestScene1::TestScene1() {
    tiledMap = std::make_unique<pk::TiledMap>(ASSETS_PATH "map/world_map.txt");
    path = tiledMap->getPath(10, 9, 20, 25);
    std::cout << '1' << '\n';
}


void pk::TestScene1::update(const float dt) {
     
}


void pk::TestScene1::render(sf::RenderWindow &window) {
    sf::RectangleShape rect(sf::Vector2f(16.f, 16.f));
    for (std::size_t i = 0; i < path.size(); i++) {
        const auto& pair = path[i];
        rect.setPosition(pair.first * 16.0f, pair.second * 16.0f);
        i == 0 || i == path.size() - 1 ? rect.setFillColor(sf::Color::Green) : rect.setFillColor(sf::Color::Red);
        window.draw(rect);
    }
}


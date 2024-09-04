#include "../../include/scene/Scene.hpp"
#include "../../include/tiledmap.hpp"
#include "../../include/ecs/Camera.hpp"


sf::Vector2f center(2300.0f, 1800.0f);
const float speed = 150.0f;


pk::TestScene1::TestScene1() {
    pk::gCamera.setZoom(1.0f);    
    pk::loadTiledMap(pk::MAIN_WORLD);
}


void pk::TestScene1::update(const float dt) {    
    pk::gCamera.updateZoom(dt);
    pk::gEcs.update(dt);
    sf::Vector2f d = pk::getDirection();
    center.x += d.x * speed * dt;
    center.y += d.y * speed * dt;
}


void pk::TestScene1::draw(sf::RenderWindow& window) {
    pk::gCamera.setCenter(center);
    pk::gCamera.draw(window);
}
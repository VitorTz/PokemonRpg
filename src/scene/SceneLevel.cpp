#include "../../include/scene/Scene.hpp"
#include "../../include/ecs/ECS.hpp"


pk::Level::Level() {    
    pk::gEcs.createSprite(
        pk::gEcs.entityCreate(0, true),
        "/home/vitor/Pictures/Assets/water-tile.png"
    );
}


void pk::Level::update(const float dt) {
    pk::gEcs.update(dt);    
}


void pk::Level::draw(sf::RenderWindow& window) {    
    pk::gCamera.draw(window);
}
#include "../../include/scene/Scene.hpp"
#include "../../include/ecs/ECS.hpp"
#include "../../include/Input.hpp"
#include "../../include/tiledmap.hpp"


pk::Level::Level() {
    // camera
        pk::gCamera.setZoom(1.0f);
        pk::gCamera.setCenter(2300.0f, 1800.0f);
    
    // load map
        pk::loadTiledMap(pk::MAIN_WORLD);

}


void pk::Level::update(const float dt) {     
    pk::gCamera.updateZoom(dt);
    pk::gEcs.update(dt);
}


void pk::Level::draw(sf::RenderWindow& window) {    
    pk::gCamera.draw(window);
}
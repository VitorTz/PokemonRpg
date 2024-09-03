#include "../../include/scene/Scene.hpp"
#include "../../include/ecs/ECS.hpp"
#include "../../include/Input.hpp"
#include <filesystem>
#include <algorithm>
#include <vector>



static void loadMap() {
    std::vector<std::pair<int, std::string>> mapSprites{};
    for (const auto& p : std::filesystem::directory_iterator(pk::MAP_SPRITES)) {
        const std::filesystem::path path = p.path();
        mapSprites.push_back({std::stoi(path.stem().string()), path.string()});
    }    
    
    std::sort(mapSprites.begin(), mapSprites.end());
    const int columns = 5;    
    int n = 0;
    float left = 0.0f;
    float top = 0.0f;

    for (const std::pair<int, std::string>& pair : mapSprites) {
        const pk::entity_t e = pk::gEcs.entityCreate(0, true);
        pk::gEcs.insertComponent<pk::sprite_t>(e, pk::sprite_t{pair.second.c_str()});
        pk::transform_t& t = pk::gEcs.getComponent<pk::transform_t>(e);
        pk::sprite_t& s = pk::gEcs.getComponent<pk::sprite_t>(e);
        t.pos = sf::Vector2f(left, top);
        t.size = (sf::Vector2f) s.sfSprite.getTexture()->getSize();
        n += 1;
        left += pk::SCREEN_W_F;
        if (n >= columns) {
            left = 0.0f;
            top += pk::SCREEN_H_F;
            n = 0;
        }
    }
}


pk::Level::Level() {
    loadMap();
    pk::gCamera.setZoom(1.0f);
    pk::gCamera.setCenter(2300.0f, 1800.0f);
}


void pk::Level::update(const float dt) {     
    const float mouseDelta = pk::gInput.getMouseWheelDelta() * dt * 2.0f;
    pk::gCamera.addZoom(mouseDelta);
    pk::gEcs.update(dt);
}


void pk::Level::draw(sf::RenderWindow& window) {    
    pk::gCamera.draw(window);
}
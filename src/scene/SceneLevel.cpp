#include "../../include/scene/Scene.hpp"
#include "../../include/ecs/ECS.hpp"
#include <filesystem>
#include <algorithm>
#include <vector>



static void loadMap() {
    std::vector<std::filesystem::path> mapSprites{};
    for (const auto& p : std::filesystem::directory_iterator(pk::MAP_SPRITES)) {
        mapSprites.push_back(p.path());
    }
    
    std::sort(
        mapSprites.begin(), 
        mapSprites.end(),
        [](const std::filesystem::path& l, const std::filesystem::path& r) {
            
        }
    );
}


pk::Level::Level() {    
    
}


void pk::Level::update(const float dt) {
    pk::gEcs.update(dt);    
}


void pk::Level::draw(sf::RenderWindow& window) {    
    pk::gCamera.draw(window);
}
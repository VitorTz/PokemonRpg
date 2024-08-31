#include <algorithm>
#include "../../include/ecs/Camera.hpp"
#include "../../include/constants.hpp"
#include "../../include/ecs/ECS.hpp"


pk::Camera::Camera() {
    this->view.setSize(pk::SCREEN_W_F, pk::SCREEN_H_F);
    this->view.setCenter(pk::SCREEN_CENTER);
    this->view.zoom(this->zoom);
    for (pk::zindex_t z = pk::ZINDEX_MIN; z <= pk::ZINDEX_MAX; z++) {        
        this->entityVecByIndex[z].reserve(pk::MAX_ENTITIES);
    }
}


void pk::Camera::insert(const pk::entity_t e) {
    const pk::zindex_t zindex = pk::gEcs.getComponent<pk::transform_t>(e).zindex;
    this->entityVecByIndex.at(zindex).push_back({0.0f, e});
    this->entityCount++;
}


void pk::Camera::erase(const pk::entity_t e) {
    const pk::zindex_t zindex = pk::gEcs.getComponent<pk::transform_t>(e).zindex;
    std::vector<std::pair<float, pk::entity_t>>& v = this->entityVecByIndex.at(zindex);
    for (std::size_t i = 0; i < v.size(); i++) {
        if (v[i].second == e) {
            v.erase(v.begin() + i);
            this->entityCount--;
            return;
        }
    }
}


void pk::Camera::draw(sf::RenderWindow& window) {
    window.setView(this->view);
    for (auto& pair1 : this->entityVecByIndex) {
        for (std::pair<float, pk::entity_t>& pair2 : pair1.second) {
            const pk::transform_t& t = pk::gEcs.getComponent<pk::transform_t>(pair2.second);
            pair2.first = t.pos.y + t.size.y / 2.0f;
        }
        std::sort(pair1.second.begin(), pair1.second.end());
        pk::gEcs.draw(window, pair1.second);
    }
    window.setView(window.getDefaultView());
}


void pk::Camera::setCenter(const sf::Vector2f& center) {
    this->view.setCenter(center);
}


void pk::Camera::addZoom(const float delta) {
    this->zoom = std::clamp(this->zoom + delta, pk::CAMERA_MIN_ZOON, pk::CAMERA_MAX_ZOON);
    this->view.zoom(this->zoom);
}


void pk::Camera::setZoom(const float z) {
    this->zoom = std::clamp(z, pk::CAMERA_MIN_ZOON, pk::CAMERA_MAX_ZOON);
    this->view.zoom(this->zoom);
}


float pk::Camera::getZoom() const {
    return this->zoom;
}


void pk::Camera::clear() {
    for (auto& pair : this->entityVecByIndex) {
        pair.second.clear();
    }
}


std::size_t pk::Camera::getEntityCount() const {
    return this->entityCount;
}
//
// Created by vitor on 9/14/24.
//
#include "Camera.h"
#include "../ecs/ECS.h"


pk::Camera::Camera() {
    this->view.setSize(pk::SCREEN_WF, pk::SCREEN_HF);
    this->view.setCenter(pk::WORLD_CENTERX, pk::WORLD_CENTERY);
    this->cameraRect.width = pk::SCREEN_WF;
    this->cameraRect.height = pk::SCREEN_HF;
    this->cameraRect.left = pk::WORLD_CENTERX - pk::SCREEN_CENTERX;
    this->cameraRect.top = pk::WORLD_CENTERY - pk::SCREEN_CENTERY;
    this->view.zoom(this->zoom);
    for (pk::zindex_t z = pk::CAMERA_MIN_ZINDEX; z <= pk::CAMERA_MAX_ZINDEX; z++) {
        this->cameraMap[z].reserve(pk::MAX_ENTITIES);
    }
}


void pk::Camera::insert(const pk::entity_t e) {
    if (this->onCamera[e] == false) {
        const pk::zindex_t zindex =pk::gEcs.getTransform(e).zindex;
        assert(zindex >= pk::CAMERA_MIN_ZINDEX && zindex <= pk::CAMERA_MAX_ZINDEX);
        this->onCamera[e] = true;
        this->mSize++;
        this->cameraMap[pk::gEcs.getTransform(e).zindex].emplace_back(0.0f, e);
    }
}


void pk::Camera::erase(pk::entity_t e) {
    if (this->onCamera[e] == true) {
        this->onCamera[e] = false;
        std::vector<std::pair<float, pk::entity_t>>& v = this->cameraMap[pk::gEcs.getTransform(e).zindex];
        for (std::size_t i = 0; i < v.size(); i++) {
            if (v[i].second == e) {
                v.erase(v.begin() + i);
                this->mSize--;
                return;
            }
        }
    }
}


void pk::Camera::clear() {
    for (auto& pair : this->cameraMap) {
        pair.second.clear();
    }
}


std::size_t pk::Camera::size() const {
    return this->mSize;
}


void pk::Camera::setCenter(const float x, const float y) {
    this->view.setCenter(
        std::clamp(x, pk::SCREEN_CENTERX, pk::WORLD_WIDTH - pk::SCREEN_CENTERX),
        std::clamp(y, pk::SCREEN_CENTERY, pk::WORLD_HEIGHT - pk::SCREEN_CENTERY)
    );
}


void pk::Camera::setCenter(const sf::Vector2f& center) {
    this->setCenter(center.x, center.y);
}


void pk::Camera::setZoom(const float z) {
    this->zoom = std::clamp(z, pk::CAMERA_MIN_ZOOM, pk::CAMERA_MAX_ZOOM);
    this->view.setSize(pk::SCREEN_SIZE);
    this->view.zoom(this->zoom);
}


void pk::Camera::addZoom(const float z) {
    this->zoom = std::clamp(this->zoom + z, pk::CAMERA_MIN_ZOOM, pk::CAMERA_MAX_ZOOM);
    this->view.setSize(pk::SCREEN_SIZE);
    this->view.zoom(this->zoom);
}


void pk::Camera::setView(sf::RenderWindow &window) const {
    window.setView(this->view);
}


void pk::Camera::draw(sf::RenderWindow &window, pk::SystemManager *system) {
    this->setView(window);
    for (auto& pair : this->cameraMap) {
        for (std::pair<float, pk::entity_t>& pair1 : pair.second) {
            const pk::transform_t& t = pk::gEcs.getTransform(pair1.second);
            pair1.first = t.pos.y + t.size.y / 2.0f;
        }
        std::sort(pair.second.begin(), pair.second.end());
        system->draw(window, pair.second);
    }
    window.setView(window.getDefaultView());
}


float pk::Camera::getZoom() const {
    return this->zoom;
}


const sf::FloatRect &pk::Camera::getCameraRect() const {
    return this->cameraRect;
}

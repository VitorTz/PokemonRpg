//
// Created by vitor on 9/14/24.
//
#include "Camera.h"
#include "ecs/ECS.h"


pk::Camera::Camera() {
    for (pk::zindex_t z = pk::CAMERA_MIN_ZINDEX; z <= pk::CAMERA_MAX_ZINDEX; z++) {
        this->cameraMap[z].reserve(pk::MAX_ENTITIES);
    }
}


void pk::Camera::insert(const pk::entity_t e) {
    if (this->onCamera[e] == false) {
        this->onCamera[e] = true;
        this->mSize++;
    }
}


void pk::Camera::erase(pk::entity_t e) {
    if (this->onCamera[e] == true) {
        this->onCamera[e] = false;
        this->mSize--;
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


void pk::Camera::draw(sf::RenderWindow &window, pk::SystemManager *system) {
    for (auto& pair : this->cameraMap) {
        for (std::pair<float, pk::entity_t>& pair1 : pair.second) {
            const pk::transform_t& t = pk::gEcs.getTransform(pair1.second);
            pair1.first = t.pos.y + t.size.y / 2.0f;
        }
        std::sort(pair.second.begin(), pair.second.end());
        system->draw(window, pair.second);
    }
}



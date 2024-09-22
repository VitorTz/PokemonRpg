//
// Created by vitor on 9/21/24.
//
#include "Camera.h"
#include <algorithm>
#include "../ecs/ECS.h"


pk::Camera::Camera() {
    for (pk::zindex_t z = pk::CAMERA_MIN_ZINDEX; z <= pk::CAMERA_MAX_ZINDEX; z++) {
        this->camera[z].reserve(pk::MAX_ENTITIES);
    }
    this->view.setSize(pk::SCREEN_W, pk::SCREEN_H);
    this->view.setCenter(pk::WORLD_CENTERX, pk::WORLD_CENTERY);
    this->view.zoom(1.0f);
}


void pk::Camera::insert(const pk::entity_t e) {
    if (this->isOnCamera[e] == false) {
        this->isOnCamera[e] = true;
        this->mSize++;
        this->camera[pk::gEcs.getTransform(e).zindex].emplace_back(0.0f, e);
    }
}


void pk::Camera::erase(const pk::entity_t e) {
    if (this->isOnCamera[e] == true) {
        this->isOnCamera[e] = false;
        this->mSize--;
        std::vector<std::pair<float, pk::entity_t>>& v = this->camera[pk::gEcs.getTransform(e).zindex];
        for (std::size_t i = 0; i < v.size(); i++) {
            if (v[i].second == e) {
                v.erase(v.begin() + i);
                return;
            }
        }
    }
}


void pk::Camera::draw(sf::RenderWindow &window, pk::SystemManager *system) {
    window.setView(this->view);
    for (auto& pair : this->camera) {
        for (std::pair<float, pk::entity_t>& pair1 : pair.second) {
            const pk::transform_t& t = pk::gEcs.getTransform(pair1.second);
            pair1.first = t.pos.y + t.size.y / 2.0f;
        }
        std::sort(pair.second.begin(), pair.second.end());
        system->draw(window, pair.second);
    }
    window.setView(window.getDefaultView());
}


void pk::Camera::setCenter(const float x, const float y) {
    this->view.setCenter(x, y);
}


void pk::Camera::setCenter(const sf::Vector2f &center) {
    this->view.setCenter(center);
}


void pk::Camera::clear() {
    for (auto& pair : this->camera) {
        pair.second.clear();
    }
    for (bool& b : this->isOnCamera) {
        b = false;
    }
}



std::size_t pk::Camera::size() const {
    return this->mSize;
}





#include "../include/Camera.hpp"
#include <stdio.h>
#include <cassert>
#include <algorithm>


pk::Camera::Camera(

) {
    for (pk::zindex_t zindex = pk::CAMERA_MIN_ZINDEX; zindex <= pk::CAMERA_MAX_ZINDEX; zindex++) {
        this->entitiesByIndex.insert({zindex, { }});
    }
    for (auto& pair : this->entitiesByIndex) {
        pair.second.reserve(pk::MAX_ENTITIES);
    }
}


void pk::Camera::init(
    const std::shared_ptr<pk::SystemManager>& system,
    const std::shared_ptr<pk::ComponentManager>& component
) {
    this->systemManager = system;
    this->componentManager = component;
}


void pk::Camera::beginDrawing() {
    BeginMode2D(this->camera);
}


void pk::Camera::endDrawing() {
    EndMode2D();
}


void pk::Camera::move(
    const float x,
    const float y
) {
    this->camera.target.x += x;
    this->camera.target.y += y;
}


void pk::Camera::setCenter(
    const Vector2 target 
) {
    this->camera.target = target;
}


void pk::Camera::setCenter(
    const float x,
    const float y
) {
    this->camera.target.x = x;
    this->camera.target.y = y;
}


Vector2 pk::Camera::getCenter() const {
    return this->camera.target;
}


void pk::Camera::insert(
    const pk::entity_t e,
    const pk::zindex_t zindex
) {
    assert(
        zindex >= pk::CAMERA_MIN_ZINDEX &&
        zindex <= pk::CAMERA_MAX_ZINDEX &&
        "Zindex out of range"
    );
    if (this->isOnCamera[e] == false) {
        this->isOnCamera[e] = true;
        this->entitiesByIndex[zindex].push_back(std::make_pair(0.0f, e));
    }    
}


void pk::Camera::erase(const pk::entity_t e) { 
    const pk::zindex_t zindex = this->componentManager->at<pk::transform_t>(e).zindex;    
    if (this->isOnCamera[e] == true) {
        this->isOnCamera[e] = false;
        std::vector<std::pair<float, pk::entity_t>>& v = this->entitiesByIndex[zindex];
        for (std::size_t i = 0; i < v.size(); i++) {
            if (v[i].second == e) {
                v.erase(v.begin() + i);
            }
        }
    }
}


void pk::Camera::draw() {
    BeginMode2D(this->camera);
        // zindex and y sort camera
        for (auto& pair : this->entitiesByIndex) {
            for (std::pair<float, pk::entity_t>& pair1 : pair.second) {
                const pk::transform_t& t = this->componentManager->at<pk::transform_t>(pair1.second);
                pair1.first = t.pos.y + t.size.y / 2.0f;
            }
            std::sort(pair.second.begin(), pair.second.end());
            for (std::pair<float, pk::entity_t>& pair1 : pair.second) {
                this->systemManager->draw(pair1.second);            
            }
        }
    EndMode2D();
}


void pk::Camera::clear() {
    for (auto& pair : this->entitiesByIndex) {
        pair.second.clear();
    }
    for (bool& i : this->isOnCamera) {
        i = false;
    }
}


std::size_t pk::Camera::size() const {
    std::size_t s = 0;
    for (auto& pair : this->entitiesByIndex) {
        s += pair.second.size();
    }
    return s;
}
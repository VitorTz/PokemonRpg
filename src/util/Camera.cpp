#include "Camera.hpp"
#include "constants.hpp"
#include "raylib.h"
#include "types.hpp"
#include <algorithm>
#include <cstddef>
#include <algorithm>
#include "../ecs/ECS.hpp"


pk::Camera::Camera() {    
    this->camera.target = Vector2{0.0f, 0.0f};
    this->camera.offset = Vector2{pk::SCREEN_CENTERX, pk::SCREEN_CENTERY};
    this->camera.zoom = 1.0f;
    for (pk::zindex_t z = pk::CAMERA_MIN_ZINDEX; z <= pk::CAMERA_MAX_ZINDEX; z++) {
        this->cameraEntities[z].reserve(pk::MAX_ENTITIES);
    }
}


void pk::Camera::addZoom(const float delta) {    
    this->camera.zoom = std::clamp(this->camera.zoom + delta, pk::CAMERA_MIN_ZOOM, pk::CAMERA_MAX_ZOOM);
}


void pk::Camera::resetZoom() {    
    this->camera.zoom = 1.0f;
}


float pk::Camera::getZoom() const {
    return this->camera.zoom;
}


void pk::Camera::setTarget(const Vector2 target) {
    this->camera.target = target;
}


void pk::Camera::setOffset(const Vector2 offset) {
    this->camera.offset = offset;
}


void pk::Camera::insert(const pk::entity_t e) {
    if (this->onCamera[e] == false) {
        this->onCamera[e] = true;
        const pk::zindex_t z = pk::gEcs.getTransform(e).zindex;
        this->cameraEntities[z].push_back({0.0f, e});
    }
}


void pk::Camera::erase(const pk::entity_t e) {
    if (this->onCamera[e] == true) {
        this->onCamera[e] = false;
        const pk::zindex_t z = pk::gEcs.getTransform(e).zindex;
        std::vector<std::pair<float, pk::entity_t>>& v = this->cameraEntities[z];
        for (std::size_t i = 0; v.size(); i++) {
            if (v[i].second == e) {
                v.erase(v.begin() + i);
                return;;
            }
        }
    }
} 


void pk::Camera::sortEntitiesByCenterYpos() {
    for (auto& pair : this->cameraEntities) {
        for (std::pair<float, pk::entity_t>& pair1 : pair.second) {
            const pk::transform_t& t = pk::gEcs.getTransform(pair1.second);
            pair1.first = t.pos.y + t.size.y / 2.0f;
        }
        std::sort(pair.second.begin(), pair.second.end());
    }
}


void pk::Camera::clear() {
    for (auto& pair : this->cameraEntities) {
        pair.second.clear();
    }
    for (bool& b : this->onCamera) {
        b = false;
    }
}


const std::map<pk::zindex_t, std::vector<std::pair<float, pk::entity_t>>>& pk::Camera::getEntities() const {
    return this->cameraEntities;
}


void pk::Camera::beginDrawing() {
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(this->camera);
}


void pk::Camera::endDrawing() {
    EndMode2D();
    EndDrawing();
}
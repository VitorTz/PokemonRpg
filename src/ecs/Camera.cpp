//
// Created by vitor on 9/28/24.
//
#include "Camera.h"
#include "ECS.h"
#include <algorithm>


pk::Camera::Camera() {
    for (pk::zindex_t z = pk::CAMERA_MIN_ZINDEX; z <= pk::CAMERA_MAX_ZINDEX; z++) {
        this->entities[z].reserve(pk::MAX_ENTITIES);
    }
}


void pk::Camera::insert(const pk::entity_t e) {
    this->entities[pk::gEcs.getTransform(e).zindex].emplace_back(0.0f, e);
}


void pk::Camera::erase(const pk::entity_t e) {
    std::vector<std::pair<float, pk::entity_t>>& v = this->entities[pk::gEcs.getTransform(e).zindex];
    for (std::size_t i = 0; i < v.size(); i++) {
        if (v[i].second == e) {
            v.erase(v.begin() + i);
            return;
        }
    }
}


void pk::Camera::draw(pk::SystemManager *systemManager) {
    this->beginDrawing();
        for (auto& pair : this->entities) {
            for (std::pair<float, pk::entity_t>& p : pair.second) {
                const pk::transform_t& t = pk::gEcs.getTransform(p.second);
                p.first = t.rect.y + t.rect.height / 2.0f;
            }
            std::sort(pair.second.begin(), pair.second.end());
            systemManager->draw(pair.second);
        }
    this->endDrawing();
}


void pk::Camera::addZoom(const float z) {
    this->camera.zoom = std::clamp(this->camera.zoom + z, pk::CAMERA_MIN_ZOOM, pk::CAMERA_MAX_ZOOM);
}


void pk::Camera::setZoom(const float z) {
    this->camera.zoom = std::clamp(z, pk::CAMERA_MIN_ZOOM, pk::CAMERA_MAX_ZOOM);
}


void pk::Camera::resetZoom() {
    this->camera.zoom = 1.0f;
}


void pk::Camera::beginDrawing() const {
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(this->camera);
}


void pk::Camera::endDrawing() const {
    EndMode2D();
    EndDrawing();
}


void pk::Camera::setTarget(const float x, const float y) {
    this->camera.target.x = std::clamp(x, pk::SCREEN_CENTERX, pk::WORLD_WIDTH - pk::SCREEN_CENTERX);
    this->camera.target.y = std::clamp(y, pk::SCREEN_CENTERY, pk::WORLD_HEIGHT - pk::SCREEN_CENTERY);
}


void pk::Camera::setTarget(const Vector2 &v) {
    this->camera.target.x = std::clamp(v.x, pk::SCREEN_CENTERX, pk::WORLD_WIDTH - pk::SCREEN_CENTERX);
    this->camera.target.y = std::clamp(v.y, pk::SCREEN_CENTERY, pk::WORLD_HEIGHT - pk::SCREEN_CENTERY);
}


void pk::Camera::move(const float x, const float y) {
    this->camera.target.x = std::clamp(this->camera.target.x + x, pk::SCREEN_CENTERX, pk::WORLD_WIDTH - pk::SCREEN_CENTERX);
    this->camera.target.y = std::clamp(this->camera.target.y + y, pk::SCREEN_CENTERY, pk::WORLD_HEIGHT - pk::SCREEN_CENTERY);
}


void pk::Camera::clear() {
    for (auto& pair : this->entities) {
        pair.second.clear();
    }
}


void pk::Camera::reset() {
    this->camera = {
        .offset = Vector2{pk::SCREEN_CENTERX, pk::SCREEN_CENTERY},
        .target = Vector2{pk::SCREEN_CENTERX, pk::SCREEN_CENTERY},
        .rotation = 0.0f,
        .zoom = 1.0f
    };
}


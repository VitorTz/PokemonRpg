//
// Created by vitor on 9/30/24.
//
#include "Camera.h"
#include "TiledMap.h"


void pk::Camera::reset() {
    this->camera = {
        .offset = Vector2{pk::SCREEN_CENTERX, pk::SCREEN_CENTERY},
        .target = Vector2{pk::SCREEN_CENTERX, pk::SCREEN_CENTERY},
        .rotation = 0.0f,
        .zoom = 2.0f
    };
}


inline void pk::Camera::addZoom(const float delta) {
    this->camera.zoom = std::clamp(this->camera.zoom + delta, pk::CAMERA_MIN_ZOOM, pk::CAMERA_MAX_ZOOM);
}


inline void pk::Camera::setZoom(const float z) {
    this->camera.zoom = std::clamp(z, pk::CAMERA_MIN_ZOOM, pk::CAMERA_MAX_ZOOM);
}


void pk::Camera::beginDrawing() {
    BeginMode2D(this->camera);
}


void pk::Camera::endDrawing() {
    EndMode2D();
}


void pk::Camera::setTarget(const float x, const float y) {
    const pk::tiled_map_t& tiledMap = pk::gTiledMap.getCurrentTiledMap();
    this->camera.target.x = std::clamp(x, pk::SCREEN_CENTERX, static_cast<float>(tiledMap.width) - pk::SCREEN_CENTERX);
    this->camera.target.y = std::clamp(y, pk::SCREEN_CENTERY,  static_cast<float>(tiledMap.height) - pk::SCREEN_CENTERY);
}


void pk::Camera::handleMouseWheelInput() {
    this->addZoom(GetMouseWheelMove() * 0.05f);
}

//
// Created by vitor on 9/30/24.
//
#include "Camera.h"
#include "../ecs/ECS.h"


pk::Camera::Camera(
    const pk::TiledMapId mapId
    ) : mapSize(pk::TILED_MAP[mapId].worldSize),
        mapId(mapId) {
    this->reset();
    for (pk::zindex_t z = pk::ZINDEX_MIN; z <= pk::ZINDEX_MAX; z++) {
        this->zIndexToEntities[z].reserve(pk::MAX_ENTITIES);
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


void pk::Camera::addZoom(const float delta) {
    this->camera.zoom = std::clamp(this->camera.zoom + delta, pk::CAMERA_MIN_ZOOM, pk::CAMERA_MAX_ZOOM);
}


void pk::Camera::setZoom(const float z) {
    this->camera.zoom = std::clamp(z, pk::CAMERA_MIN_ZOOM, pk::CAMERA_MAX_ZOOM);
}


void pk::Camera::draw(pk::SystemManager *system) {
    pk::ECS* ecs = pk::ECS::getInstance(this->mapId);
    this->beginDrawing();
        for (auto& p : this->zIndexToEntities) {
            for (std::pair<float, pk::entity_t>& pair : p.second) {
                const pk::transform_t& t = ecs->getTransform(pair.second);
                pair.first = t.pos.y + t.size.y / 2.0f;
            }
            std::sort(p.second.begin(), p.second.end());
            system->draw(p.second);
        }
    this->endDrawing();
}


void pk::Camera::insert(const pk::entity_t e) {
    pk::ECS* ecs = pk::ECS::getInstance(this->mapId);
    const pk::zindex_t z = ecs->getTransform(e).zindex;
    assert(z >= pk::ZINDEX_MIN && pk::ZINDEX_MAX);
    if (this->onCameraEntities[e] == false) {
        this->mSize++;
        this->onCameraEntities[e] = true;
        this->zIndexToEntities[z].emplace_back(0.0f, e);
    }
}


void pk::Camera::erase(const pk::entity_t e) {
    pk::ECS* ecs = pk::ECS::getInstance(this->mapId);
    if (this->onCameraEntities[e] == true) {
        this->onCameraEntities[e] = false;
        const pk::zindex_t z = ecs->getTransform(e).zindex;
        this->mSize--;
        std::vector<std::pair<float, pk::entity_t>>& v = this->zIndexToEntities[z];
        for (std::size_t i = 0; i < v.size(); i++) {
            if (v[i].second == e) {
                v.erase(v.begin() + i);
                return;
            }
        }
    }
}


void pk::Camera::beginDrawing() const {
    BeginMode2D(this->camera);
}


void pk::Camera::endDrawing() const {
    EndMode2D();
}


void pk::Camera::setTarget(const float x, const float y) {
    this->camera.target.x = std::clamp(x, pk::SCREEN_CENTERX, this->mapSize.x - pk::SCREEN_CENTERX);
    this->camera.target.y = std::clamp(y, pk::SCREEN_CENTERY, this->mapSize.y - pk::SCREEN_CENTERY);
}


void pk::Camera::setTarget(const Vector2 &v) {
    this->setTarget(v.x, v.y);
}


void pk::Camera::move(const float x, const float y) {
    this->setTarget(this->camera.target.x + x, this->camera.target.y + y);
}


void pk::Camera::clear() {
    for (auto& pair : this->zIndexToEntities) {
        pair.second.clear();
    }
}


std::size_t pk::Camera::size() const {
    return this->mSize;
}


float pk::Camera::getZoom() const {
    return this->camera.zoom;
}


void pk::Camera::handleUserInput() {
    this->addZoom(GetMouseWheelMove() * 0.05f);
}

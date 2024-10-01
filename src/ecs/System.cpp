//
// Created by vitor on 9/30/24.
//
#include "ECS.h"
#include "../util/Camera.h"

pk::SystemManager::SystemManager() {
    for (pk::zindex_t z = pk::CAMERA_MIN_ZINDEX; z <= pk::CAMERA_MAX_ZINDEX; z++) {
        this->z_index_to_entities[z].reserve(pk::MAX_ENTITIES);
    }
    for (pk::entity_t e = 0; e < pk::MAX_ENTITIES; e++) {
        this->entity_to_components[e].reserve(pk::NUM_COMPONENTS);
    }
    this->component_to_entities[pk::id::transform].reserve(pk::MAX_ENTITIES);
    this->component_to_entities[pk::id::sprite].reserve(pk::MAX_ENTITIES / 2);
    this->component_to_entities[pk::id::sprite_animation].reserve(pk::MAX_ENTITIES / 3);
    this->component_to_entities[pk::id::movement].reserve(pk::MAX_ENTITIES / 4);
    this->component_to_entities.emplace(pk::id::player, std::unordered_set<pk::entity_t>());
    assert(this->component_to_entities.size() == pk::NUM_COMPONENTS);
}


void pk::SystemManager::insert(const pk::entity_t e, const pk::component_t componentId) {
    this->component_to_entities[componentId].insert(e);
    this->entity_to_components[e].insert(componentId);
}


void pk::SystemManager::erase(const pk::entity_t e, const pk::component_t componentId) {
    this->component_to_entities[componentId].erase(e);
    this->entity_to_components[e].erase(componentId);
}


void pk::SystemManager::entityDestroy(const pk::entity_t e) {
    for (const pk::component_t id : this->entity_to_components[e]) {
        this->component_to_entities[id].erase(e);
    }
    this->entity_to_components[e].clear();
}


void pk::SystemManager::update(const float dt) {
    this->update_movement(dt);
    this->update_sprite_animation(dt);
    this->update_player(dt);
}


void pk::SystemManager::addToCamera(const pk::entity_t e) {
    const pk::zindex_t z = pk::gEcs.getTransform(e).zindex;
    assert(z >= pk::CAMERA_MIN_ZINDEX && z <= pk::CAMERA_MAX_ZINDEX);
    if (this->onCameraEntities[e] == false) {
        this->onCameraEntities[e] = true;
        this->z_index_to_entities[z].emplace_back(0.0f, e);
    }
}


void pk::SystemManager::rmvFromCamera(pk::entity_t e) {
    const pk::zindex_t z = pk::gEcs.getTransform(e).zindex;
    if (this->onCameraEntities[e] == true) {
        this->onCameraEntities[e] = false;
        std::vector<std::pair<float, pk::entity_t>>& v = this->z_index_to_entities[z];
        for (std::size_t i = 0; i < v.size(); i++) {
            if (v[i].second == e) {
                v.erase(v.begin() + i);
                return;
            }
        }
    }
}


void pk::SystemManager::draw() {
    pk::gCamera.beginDrawing();
        for (auto& p : this->z_index_to_entities) {
            for (std::pair<float, pk::entity_t>& pair : p.second) {
                const pk::transform_t& transform = pk::gEcs.getTransform(pair.second);
                pair.first = transform.pos.y + transform.size.y / 2.0f;
            }
            std::sort(p.second.begin(), p.second.end());
            for (std::pair<float, pk::entity_t>& pair : p.second) {
                for (const pk::component_t id : this->entity_to_components[pair.second]) {
                    switch (id) {
                        case pk::id::sprite:
                            pk::SystemManager::sprite_draw(pair.second);
                        break;
                        case pk::id::sprite_animation:
                            pk::SystemManager::sprite_animation_draw(pair.second);
                        break;
                        default:
                            break;
                    }
                }
            }
        }
    pk::gCamera.endDrawing();
}


void pk::SystemManager::clear() {
    for (auto& pair : this->z_index_to_entities) {
        pair.second.clear();
    }
    for (auto& pair : this->entity_to_components) {
        pair.second.clear();
    }
    for (auto& pair : this->component_to_entities) {
        pair.second.clear();
    }
}


void pk::SystemManager::update_sprite_animation(const float dt) {
    for (const pk::entity_t e : this->component_to_entities[pk::id::sprite_animation]) {
        auto& animation = pk::gEcs.getComponent<pk::sprite_animation_t, pk::id::sprite_animation>(e);
        animation.counter++;
        if (animation.counter > animation.speed) {
            animation.counter = 0;
            animation.frame = (animation.frame + 1) % animation.maxFrame;
        }
        animation.rect.x = static_cast<float>(animation.frame % animation.cols) * animation.rect.width;
        animation.rect.y = static_cast<float>(animation.frame / animation.cols) * animation.rect.height;
    }
}


void pk::SystemManager::update_movement(const float dt) {
    for (const pk::entity_t e : this->component_to_entities[id::movement]) {

    }
}


void pk::SystemManager::update_player(const float dt) {
    for (const pk::entity_t e : this->component_to_entities[id::player]) {
        pk::transform_t& transform = pk::gEcs.getTransform(e);
        auto& player = pk::gEcs.getComponent<pk::player_t, id::player>(e);
        auto& spriteAnimation = pk::gEcs.getComponent<pk::sprite_animation_t, id::sprite_animation>(e);
        const auto& movement = pk::gEcs.getComponent<pk::movement_t, id::movement>(e);

        if (movement.direction[0] == 'i') {
            spriteAnimation.rect.x = 0;
        }
        pk::gCamera.setTarget(10.0f, 10.0f);

        switch (movement.direction[1]) {
            case 'd':
                spriteAnimation.rect.y = 0.0f;
                break;
            case 'l':
                spriteAnimation.rect.y = pk::PLAYER_SIZE;
                break;
            case 'r':
                spriteAnimation.rect.y = pk::PLAYER_SIZE * 2;
                break;
            case 'u':
                spriteAnimation.rect.y = pk::PLAYER_SIZE * 3;
                break;
            default:
                break;
        }
    }
}


void pk::SystemManager::sprite_draw(const pk::entity_t e) {
    const auto& sprite = pk::gEcs.getComponent<pk::sprite_t, id::sprite>(e);
    const pk::transform_t& transform = pk::gEcs.getTransform(e);
    DrawTextureV(sprite.texture, transform.pos, WHITE);
}


void pk::SystemManager::sprite_animation_draw(const pk::entity_t e) {
    const auto& animation = pk::gEcs.getComponent<pk::sprite_animation_t, pk::id::sprite_animation>(e);
    const pk::transform_t& transform = pk::gEcs.getTransform(e);
    DrawTextureRec(animation.texture, animation.rect, transform.pos, WHITE);
}





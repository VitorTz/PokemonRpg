//
// Created by vitor on 9/14/24.
//
#include "components.h"
#include "System.h"
#include "ECS.h"
#include "../TexturePool.h"

float waterTime = 0.0f;
sf::Sprite waterSprite{};
std::size_t waterSpriteIndex = 0;


void pk::WaterSystem::update(const float dt) {
    waterTime += dt;
    if (waterTime >= pk::ANIMATION_WATER_TIME) {
        waterTime = 0.0f;
        waterSpriteIndex = (waterSpriteIndex + 1) % pk::WATER_SPRITES_NUM;
    }
}


void pk::WaterSystem::draw(sf::RenderWindow &window, const pk::entity_t e) {
    const pk::water_t& water = pk::gEcs.getComponent<pk::water_t>(e);
    if (water.isCoast) {
        pk::gTexturePool.set(&waterSprite, pk::WATER_SPRITES[waterSpriteIndex + 2]);
        waterSprite.setPosition(pk::WATER_POS_COAST);
    } else {
        pk::gTexturePool.set(&waterSprite, pk::WATER_SPRITES[waterSpriteIndex]);
        waterSprite.setPosition(pk::WATER_POS);
    }
    window.draw(waterSprite);
}

//
// Created by vitor on 9/14/24.
//
#include "components.h"
#include "System.h"
#include "ECS.h"
#include "../util/TexturePool.h"


void pk::WaterSystem::update(const float dt) {
    this->counter.update();
}


void pk::WaterSystem::draw(sf::RenderWindow &window, const pk::entity_t e) {
    const pk::water_t& water = pk::gEcs.getComponent<pk::water_t>(e);
    const std::uint32_t spriteIndex = this->counter.getCounter();
    if (water.isCoast) {
        pk::gTexturePool.set(&this->waterSprite, pk::WATER_SPRITES[spriteIndex + 2]);
        waterSprite.setPosition(pk::WATER_POS_COAST);
    } else {
        pk::gTexturePool.set(&waterSprite, pk::WATER_SPRITES[spriteIndex]);
        waterSprite.setPosition(pk::WATER_POS);
    }
    window.draw(waterSprite);
}

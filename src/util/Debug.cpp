//
// Created by vitor on 9/20/24.
//
#include "Debug.h"
#include <sstream>
#include "../ecs/player.h"
#include "../window/Camera.h"
#include "../ecs/ECS.h"
#include "util.h"


pk::Debug::Debug() {
    pk::gFontPool.set(&this->text, pk::Regular);
    this->text.setCharacterSize(16);
    this->text.setFillColor(sf::Color::White);
}


void pk::Debug::draw(sf::RenderWindow &window) {
    pk::gCamera.setView(window);
    pk::drawFloatRect(pk::gPlayer.collideRect, sf::Color::Blue, window);
    pk::drawFloatRect(pk::gPlayer.actionRect, sf::Color::Red, window);
    window.setView(window.getDefaultView());
}


#include "../include/Scene.hpp"
#include "../include/Ecs.hpp"


pk::TitleScreen::TitleScreen() {
    pk::gEcs.createSprite(pk::WINDOW_ICON, 0);
}


void pk::TitleScreen::update(const float dt) {
    pk::gEcs.update(dt);
}


void pk::TitleScreen::draw() {
    pk::gEcs.draw();
}
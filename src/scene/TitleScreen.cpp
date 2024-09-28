//
// Created by vitor on 9/28/24.
//
#include "Scene.h"
#include "../util/TexturePool.h"
#include "../util/util.h"


pk::TitleScreen::TitleScreen(

) : background(pk::gTexturePool.get(pk::randomFile(ASSETS_PATH "skies/").c_str())),
    logo(pk::gTexturePool.get(ASSETS_PATH "icons/Pokemon-Title.png")),
    pressSpace(pk::gTexturePool.get(ASSETS_PATH "icons/Press-Space.png")) {

}


void pk::TitleScreen::update(const float dt) {
    const float distance = dt * 100.0f;
    for (Vector2& v : this->backgroundPos) {
        v.x -= distance;
        if (v.x + pk::SCREEN_W < 0.0f) {
            v.x += pk::SCREEN_W * 2.0f;
        }
    }
    if (IsKeyPressed(KEY_SPACE)) {
        pk::gSceneManager.changeScene(pk::LevelScreenId);
    }
}


void pk::TitleScreen::draw() {
    BeginDrawing();
    ClearBackground(BLACK);
        DrawTextureV(this->background, this->backgroundPos[0], WHITE);
        DrawTextureRec(this->background, Rectangle{0.0f, 0.0f, -pk::SCREEN_W, pk::SCREEN_H}, this->backgroundPos[1], WHITE);
        DrawTextureV(
            this->logo,
            Vector2{
                pk::SCREEN_CENTERX - static_cast<float>(this->logo.width) / 2.0f,
                pk::SCREEN_CENTERY - static_cast<float>(this->logo.height) / 2.0f
            },
            WHITE
        );
        DrawTextureV(
            this->pressSpace,
            Vector2{
                pk::SCREEN_CENTERX - static_cast<float>(this->pressSpace.width) / 2.0f,
                pk::SCREEN_CENTERY - static_cast<float>(this->logo.height) / 2.0f + static_cast<float>(this->pressSpace.height) + 30.0f
            },
            WHITE
        );
    EndDrawing();
}



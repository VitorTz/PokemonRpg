//
// Created by vitor on 9/15/24.
//
#include "System.h"
#include "ECS.h"
#include "../util/util.h"


pk::BoatSystem::BoatSystem() {
    this->boatSprites = pk::getFilesFromDir(ASSETS_PATH "graphics/objects/boat");
    this->emptyRoutes.push(
        {
            {-200.0f, pk::WORLD_HEIGHT - 200.0f},
            {pk::WORLD_WIDTH + 200.0f, pk::WORLD_HEIGHT - 150.0f}
        }
    );
    this->emptyRoutes.push(
        {
            {-200.0f, pk::WORLD_HEIGHT - 100.0f},
            {pk::WORLD_WIDTH + 200.0f, pk::WORLD_HEIGHT - 50.0f}
        }
    );
    this->emptyRoutes.push(
        {
            { pk::WORLD_WIDTH + 200.0f, pk::WORLD_HEIGHT - 320.0f},
            {-200.0f, pk::WORLD_HEIGHT - 400.0f}
        }
    );
}


void pk::BoatSystem::update([[maybe_unused]] const float dt) {
    for (const pk::entity_t e : this->entities) {
        pk::bezier_curve_t& bezier = pk::gEcs.getComponent<pk::bezier_curve_t>(e);
        pk::boat_t& boat = pk::gEcs.getComponent<pk::boat_t>(e);
        switch (boat.state) {
            case pk::State::Paused:
                if (this->emptyRoutes.empty() == false) {
                    const std::vector<sf::Vector2f> route = this->emptyRoutes.front();
                    this->emptyRoutes.pop();
                    bezier.points = route;
                    this->entityToRoute.insert({e, route});
                    bezier.currentTime = 0.0f;
                    bezier.maxTime = pk::randfloat(20.0f, 40.0f);
                    pk::changeEntitySprite(e, pk::randomChoice(this->boatSprites).c_str());
                    boat.state = pk::State::Active;
                }
                break;
            case pk::State::Active:
                if (bezier.currentTime >= bezier.maxTime) {
                    boat.state = pk::State::Paused;
                    this->emptyRoutes.push(this->entityToRoute[e]);
                    this->entityToRoute.erase(e);
                }
                break;
            default:
                break;
        }
    }
}


void pk::BoatSystem::draw([[maybe_unused]] sf::RenderWindow &window, [[maybe_unused]] pk::entity_t e) {

}


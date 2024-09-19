//
// Created by vitor on 9/15/24.
//
#include "System.h"
#include "ECS.h"
#include "../util/util.h"


pk::BoatSystem::BoatSystem() {
    for (const std::filesystem::path& p : pk::getFilesFromDir(ASSETS_PATH "graphics/objects/boat")) {
        this->boatSprites.push_back(pk::gTexturePool.get(p.c_str()));
    }
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
    this->emptyRoutes.push(
        {
            { pk::WORLD_WIDTH + 200.0f, pk::WORLD_HEIGHT - 380.0f},
            { pk::WORLD_CENTERX, WORLD_HEIGHT - 100.0f},
            {-200.0f, pk::WORLD_HEIGHT - 300.0f}
        }
    );
}


void pk::BoatSystem::update(const float dt) {
    this->currentTime += dt;
    for (const pk::entity_t e : this->entities) {
        pk::bezier_curve_t& bezier = pk::gEcs.getComponent<pk::bezier_curve_t>(e);
        pk::boat_t& boat = pk::gEcs.getComponent<pk::boat_t>(e);
        switch (boat.state) {
            case pk::State::Paused:
                if (this->emptyRoutes.empty() == false && this->currentTime >= this->nextDepartureTime) {
                    // New route
                        const std::vector<sf::Vector2f> route = this->emptyRoutes.front();
                        this->emptyRoutes.pop();
                        bezier.points = route;
                        bezier.currentTime = 0.0f;
                        bezier.maxTime = pk::randfloat(20.0f, 40.0f); // Travel time
                        this->entityToRoute.insert({e, route});
                    // Next Departure
                        this->nextDepartureTime = pk::randfloat(1.0f, 10.f);
                        this->currentTime = 0.0f;
                    // Set random boat sprite
                        pk::changeEntitySprite(e, pk::randomChoice(this->boatSprites));
                        pk::transform_t& t = pk::gEcs.getTransform(e);
                        // Flip sprite horizontally if travel is right to left
                        t.scale.x = route.back().x < pk::WORLD_CENTERX ? -1.0f : 1.0f;
                    // Boat is active
                        boat.state = pk::State::Active;
                    printf("[BOAT -> (%.2f, %.2f) -> (%.2f, %.2f)]\n", route[0].x, route[0].y, route.back().x, route.back().y);
                    printf("[BOAT -> NEXT DEPARTURE IN %.2f sec]\n", this->nextDepartureTime);
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


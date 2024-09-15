//
// Created by vitor on 9/14/24.
//
#include "System.h"
#include "ECS.h"
#include "../util/util.h"


void pk::BezierCurveSystem::update(const float dt) {
    for (const pk::entity_t e : this->entities) {
        pk::transform_t& transform = pk::gEcs.getTransform(e);
        pk::bezier_curve_t& bezier = pk::gEcs.getComponent<pk::bezier_curve_t>(e);
        if (bezier.points.size() <= 1 || bezier.currentTime >= bezier.maxTime) {
            continue;
        }
        bezier.currentTime += dt;
        const float t = pk::getTimePercentage(bezier.currentTime, bezier.maxTime);
        const int n = bezier.points.size() - 1;
        sf::Vector2f C{0.0f, 0.0f};
        for (int k = 0; k < n+1; k++) {
            const int b_coeff = pk::binomialCoefficient(n, k);
            const double bernstein_poly = static_cast<double>(b_coeff) * std::pow(t, k) * std::pow(1.0f - t, n - k);
            C = pk::vector2Add(C, pk::vector2Scale(bezier.points[k], bernstein_poly));
        }
        transform.pos = C;
    }
}


void pk::BezierCurveSystem::draw([[maybe_unused]] sf::RenderWindow &window, [[maybe_unused]] pk::entity_t e) {
    
}

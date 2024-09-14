//
// Created by vitor on 9/14/24.
//
#include "util.h"
#include "ecs/ECS.h"


std::random_device dev;
std::mt19937 rng(dev());


unsigned long pk::hash(const char* s) {
    unsigned long hash = 5381;
    int c;
    while ((c = *s++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}


int pk::randint(const int start, const int end) {
    std::uniform_int_distribution<std::mt19937::result_type> dist(start, end);
    return static_cast<int>(dist(rng));
}


float pk::randfloat(const float start, const float end) {
    std::uniform_real_distribution<float> dist(start, end);
    return dist(rng);
}


void pk::addSpriteToEntity(const pk::entity_t e, const char *fileName) {
    pk::gEcs.insertComponent<pk::sprite_t>(e, pk::sprite_t{fileName});
    const pk::sprite_t& s = pk::gEcs.getComponent<pk::sprite_t>(e);
    pk::transform_t& t = pk::gEcs.getTransform(e);
    t.size = s.size;
}


std::filesystem::path pk::choiceRandomFile(const char *dir) {
    std::vector<std::filesystem::path> files{};
    std::filesystem::path returnPath{};
    for (auto& p : std::filesystem::directory_iterator(dir)) {
        const std::filesystem::path& path = p.path();
        if (std::filesystem::is_regular_file(path)) {
            files.push_back(path);
        }
    }
    returnPath = pk::randomChoice(files);
    return returnPath;
}


void pk::addCollisionBoxStaticToEntity(pk::entity_t e) {
    const pk::transform_t& t = pk::gEcs.getTransform(e);
    pk::gEcs.insertComponent<pk::collision_box_static_t>(
        e, pk::collision_box_static_t{sf::FloatRect(t.pos.x, t.pos.y, t.size.x, t.size.y)}
    );
}


void pk::createCollisionBoxStatic(pk::entity_t e, const sf::Vector2f &pos, const sf::Vector2f &size) {
    pk::transform_t& t = pk::gEcs.getTransform(e);
    t.pos = pos;
    t.size = size;
    pk::gEcs.insertComponent<pk::collision_box_static_t>(
        e,
        pk::collision_box_static_t{sf::FloatRect(t.pos.x, t.pos.y, t.size.x, t.size.y)}
    );
}


void pk::normalizeVec(sf::Vector2f *v) {
    const float m = std::sqrt(v->x * v->x + v->y * v->y);
    if (m > 1.0f) {
        v->x /= m;
        v->y /= m;
    }
}


sf::Vector2f pk::getMoveDirection(
    const sf::Keyboard::Key left,
    const sf::Keyboard::Key right,
    const sf::Keyboard::Key top,
    const sf::Keyboard::Key bottom
) {
    sf::Vector2f d{0.0f, 0.0f};
    if (sf::Keyboard::isKeyPressed(top)) {
        d.y = -1.0f;
    } else if (sf::Keyboard::isKeyPressed(bottom)) {
        d.y = 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(left)) {
        d.x = -1.0f;
    } else if (sf::Keyboard::isKeyPressed(right)) {
        d.x = 1.0f;
    }
    pk::normalizeVec(&d);
    return d;
}


sf::Vector2f pk::getMoveDirection() {
    sf::Vector2f d{0.0f, 0.0f};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        d.y = -1.0f;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        d.y = 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        d.x = -1.0f;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        d.x = 1.0f;
    }
    pk::normalizeVec(&d);
    return d;
}
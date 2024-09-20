//
// Created by vitor on 9/14/24.
//
#include "util.h"
#include "../ecs/ECS.h"


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

double pk::randDouble(const double start, const double end) {
    std::uniform_real_distribution<double> dist(start, end);
    return dist(rng);
}


void pk::addSpriteToEntity(const pk::entity_t e, const char *fileName) {
    pk::gEcs.insertComponent<pk::sprite_t>(e, pk::sprite_t{fileName});
    const pk::sprite_t& s = pk::gEcs.getComponent<pk::sprite_t>(e);
    pk::transform_t& t = pk::gEcs.getTransform(e);
    t.size = s.size;
    t.pos.x += t.size.x / 2.0f;
    t.pos.y += t.size.y / 2.0f;
}


void pk::addSpriteAnimation(
    const pk::entity_t e,
    const pk::AssetId assetId,
    const pk::animation_speed_t animationSpeed
) {
    const pk::asset_t& asset = pk::ASSETS_MAP.at(assetId);
    pk::gEcs.insertComponent<pk::sprite_animation_t>(e, pk::sprite_animation_t{asset, animationSpeed});
    pk::gEcs.getTransform(e).size = { static_cast<float>(asset.spriteWidth), static_cast<float>(asset.spriteHeight)};
}


void pk::changeEntitySprite(const pk::entity_t e, const char *fileName) {
    pk::transform_t& t = pk::gEcs.getTransform(e);
    pk::sprite_t& s = pk::gEcs.getComponent<pk::sprite_t>(e);
    s = pk::sprite_t{fileName};
    t.size = s.size;
}

void pk::changeEntitySprite(const pk::entity_t e, const sf::Sprite &sprite) {
    pk::transform_t& t = pk::gEcs.getTransform(e);
    pk::sprite_t& s = pk::gEcs.getComponent<pk::sprite_t>(e);
    s.sfSprite = sprite;
    s.size = static_cast<sf::Vector2f>(sprite.getTexture()->getSize());
    t.size = s.size;
}



std::vector<std::filesystem::path> pk::getFilesFromDir(const char *dir) {
    std::vector<std::filesystem::path> v{};
    for (const auto& p : std::filesystem::directory_iterator(dir)) {
        v.emplace_back(p.path());
    }
    return v;
}


std::filesystem::path pk::randomFile(const char *dir) {
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


float pk::easeIn(const float t) {
    return t * t;
}


float pk::getTimePercentage(const float currentTime, const float maxTime) {
    return std::clamp(currentTime / maxTime, 0.0f, 1.0f);
}


sf::Vector2f pk::lerp(const sf::Vector2f &start, const sf::Vector2f &end, float t) {
    t = std::clamp(t, 0.0f, 1.0f);
    const sf::Vector2f r(start.x + (end.x - start.x) * t, start.y + (end.y - start.y) * t);
    return r;
}


void pk::printVec2f(const sf::Vector2f &v) {
    printf("Vector2f(%.2f, %.2f)\n", v.x, v.y);
}


void pk::printFloatRect(const sf::FloatRect &rect) {
    printf("FloatRect(%.2f, %.2f, %.2f, %.2f)\n", rect.left, rect.top, rect.width, rect.height);
}


sf::Vector2f pk::vector2Scale(const sf::Vector2f &v, const float scale) {
    const sf::Vector2f r{v.x * scale, v.y * scale};
    return r;
}


sf::Vector2f pk::vector2Scale(const sf::Vector2f &v, const double scale) {
    const sf::Vector2f r{static_cast<float>(v.x * scale), static_cast<float>(v.y * scale)};
    return r;
}

sf::Vector2f pk::vector2Add(const sf::Vector2f &v1, const sf::Vector2f &v2) {
    const sf::Vector2f r{v1.x + v2.x, v1.y + v2.y};
    return r;
}


int pk::binomialCoefficient(const int n, const int k) {
    double res = 1;
    for (int i = 1; i <= k; ++i)
        res = res * (n - k + i) / i;
    return static_cast<int>(res + 0.01);
}


//
// Created by vitor on 9/14/24.
//

#ifndef UTIL_H
#define UTIL_H
#include "../pokemon.h"

namespace pk {

    unsigned long hash(const char* s);
    float randfloat(float start, float end);
    int randint(int start, int end);

    void printVec2f(const sf::Vector2f& v);
    void printFloatRect(const sf::FloatRect& rect);

    std::vector<std::filesystem::path> getFilesFromDir(const char* dir);
    std::filesystem::path randomFile(const char* dir);

    template<typename T>
    const T& randomChoice(const std::vector<T>& v) {
        assert(v.empty() == false);
        return v[pk::randint(0, v.size() - 1)];
    }

    template<typename T, std::size_t size>
    const T& randomChoice(const std::array<T, size>& v) {
        assert(v.empty() == false);
        return v[pk::randint(0, v.size() - 1)];
    }

    void addSpriteToEntity(pk::entity_t e, const char* fileName);
    void addSpriteAnimation(
        pk::entity_t e,
        const char* fileName,
        const sf::Vector2f& spriteSize,
        std::uint32_t animationSpeed,
        std::uint32_t rows,
        std::uint32_t cols
    );

    void changeEntitySprite(pk::entity_t e, const char* fileName);
    void changeEntitySprite(pk::entity_t e, const sf::Sprite& sprite);

    void addCollisionBoxStaticToEntity(pk::entity_t e);
    void createCollisionBoxStatic(pk::entity_t e, const sf::Vector2f& pos, const sf::Vector2f& size);

    void normalizeVec(sf::Vector2f* v);
    sf::Vector2f getMoveDirection(sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key top, sf::Keyboard::Key bottom);
    sf::Vector2f getMoveDirection();

    float easeIn(float t);
    float getTimePercentage(float currentTime, float maxTime);

    sf::Vector2f lerp(const sf::Vector2f& start, const sf::Vector2f& end, float t);
    sf::Vector2f vector2Scale(const sf::Vector2f& v, float scale);
    sf::Vector2f vector2Scale(const sf::Vector2f& v, double scale);
    sf::Vector2f vector2Add(const sf::Vector2f& v1, const sf::Vector2f& v2);
    int binomialCoefficient(int n, int k);

}

#endif //UTIL_H
